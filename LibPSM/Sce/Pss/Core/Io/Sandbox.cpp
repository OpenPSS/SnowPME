#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Edata/EdataStream.hpp>

#include <filesystem>
#include <sys/stat.h>
#include <mono/mono.h>

#include <LibShared.hpp>

using namespace Shared;
using namespace Shared::Debug;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Edata;

namespace Sce::Pss::Core::Io {

	Sandbox* Sandbox::ApplicationSandbox = nullptr;

	Sandbox::Sandbox(std::string gameFolder) {
		if (Sandbox::ApplicationSandbox != nullptr) {
			delete Sandbox::ApplicationSandbox;
		}

		std::filesystem::path gamePath = std::filesystem::path(gameFolder);
		
		// used for PSVita TargetImplementation only
		std::filesystem::path roPath = std::filesystem::path(gameFolder).append("RO");
		std::filesystem::path rwPath = std::filesystem::path(gameFolder).append("RW");

		// accessible files
		std::filesystem::path applicationPath;
		std::filesystem::path documentsPath;
		std::filesystem::path tempPath;

		// system paths
		std::filesystem::path licensePath;
		std::filesystem::path systemPath;

		if (Config::TargetImplementation == RuntimeImplementation::PSVita || std::filesystem::exists(roPath))
		{
			applicationPath = std::filesystem::path(std::filesystem::absolute(roPath).string()).append("Application");
			licensePath = std::filesystem::path(std::filesystem::absolute(roPath).string()).append("License");

			documentsPath = std::filesystem::path(std::filesystem::absolute(rwPath).string()).append("Documents");
			tempPath = std::filesystem::path(std::filesystem::absolute(rwPath).string()).append("Temp");
			systemPath = std::filesystem::path(std::filesystem::absolute(rwPath).string()).append("System");

		}
		else {
			applicationPath = std::filesystem::path(gameFolder).append("Application");
			licensePath = std::filesystem::path(gameFolder).append("License");
			documentsPath = std::filesystem::path(gameFolder).append("Documents");
			tempPath = std::filesystem::path(gameFolder).append("Temp");
			systemPath = std::filesystem::path(gameFolder).append("System");
		}



		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(applicationPath).string(), "/Application", false, false, false));
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(tempPath).string(), "/Temp", true, false, false));
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(documentsPath).string(), "/Documents", true, false, false));

		// system directories
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(licensePath).string(), "/License", false, false, true));
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(systemPath).string(), "/System", false, false, true));

		// emulated dir
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(gamePath).string(), "/", false, true, false));


		this->currentWorkingDirectory = "/";
		Sandbox::ApplicationSandbox = this;

		this->readLicenseData();

	}

	int Sandbox::readLicenseData() {
		if (this->PathExist("/License/FAKE.rif", true)) {
			this->GameDrmProvider = new PsmDrm("/License/FAKE.rif");
			ReturnErrorable(this->GameDrmProvider);
		}
		return PSM_ERROR_NO_ERROR;
	}

	Sandbox::~Sandbox() {
		// Iterate over all fileystems
		for (FileSystem* filesystem : this->filesystems) {
			delete filesystem; // delete the filesystem
		}

		if (this->GameDrmProvider != nullptr) // delete game drm provider
			delete this->GameDrmProvider;

		Sandbox::filesystems.clear(); // Clear the filesystems vector
	}
	
	// Some functions require handling via filepath,
	// in these cases, the fstream needs to be created again
	void Sandbox::reopen(PsmFileDescriptor* handle) {
		if (handle->opened && !handle->directory && handle->edataStream != NULL) {
			// Close the file
			size_t oldPos = handle->edataStream->Tell();

			if(handle->edataStream != nullptr)
				delete handle->edataStream;

			// Open the file again
			handle->edataStream = new EdataStream(handle->realPath, handle->iflags, this->GameDrmProvider);

			// Seek to where we were.
			handle->edataStream->Seek(oldPos, SCE_PSS_FILE_SEEK_TYPE_BEGIN);
		}
	}

	// Determines which "FileSystem" a given file is in,
	// eg /Application or /Documents, 
	FileSystem* Sandbox::findFilesystem(std::string sandboxedPath, bool includeSystem) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		for (FileSystem* filesystem : Sandbox::filesystems) {
			if (String::StringUtil::ToLower(absPath).starts_with(String::StringUtil::ToLower(filesystem->SandboxPath()))) {
				if (filesystem->IsSystem() && !includeSystem) continue;

				return filesystem;
			}
		}

		throw std::exception("FileSystem not found ?? ??");
	}

	size_t Sandbox::ReadFile(PsmFileDescriptor* handle, size_t numbBytes, char* buffer) {
		return handle->edataStream->Read(buffer, numbBytes);
	}

	int Sandbox::ReadDirectory(PsmFileDescriptor* handle, ScePssFileInformation_t* fileInfo) {

		memset(fileInfo, 0, sizeof(ScePssFileInformation_t));

		if (handle->emulated) { // handle "/" emulated directory, display all sandboxed paths
			if (handle->emulatedFilePosition >= this->filesystems.size()) {
				return PSM_ERROR_PATH_NOT_FOUND;
			}
			else {
				FileSystem* targetFs = this->filesystems[handle->emulatedFilePosition];
				handle->emulatedFilePosition++;
				
				if (targetFs->IsSystem()) // dont show system filesystems.
					return this->ReadDirectory(handle, fileInfo);

				if (targetFs->IsEmulated()) // dont show emulated filesystems
					return this->ReadDirectory(handle, fileInfo);

				std::string filename = String::Path::GetFilename(targetFs->SandboxPath());

				ScePssFileInformation_t psmPathInformation = this->Stat(targetFs->SandboxPath(), filename);
				memcpy(fileInfo, &psmPathInformation, sizeof(ScePssFileInformation_t));
				
				return PSM_ERROR_NO_ERROR;

			}
		}
		else {
			if (handle->directoryFd == NULL)
				return PSM_ERROR_INVALID_PARAMETER;

			int error =  handle->directoryFd->Next(fileInfo);
			
			if (error != PSM_ERROR_NO_ERROR)
				return error;

			return PSM_ERROR_NO_ERROR;
		}
	}

	ScePssFileInformation_t Sandbox::Stat(std::string sandboxedPath, std::string setName) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		FileSystem* filesystem = this->findFilesystem(sandboxedPath, false);

		struct stat stats;
		stat(this->LocateRealPath(absPath, false).c_str(), &stats);

		ScePssFileInformation_t psmPathInformation;
		memset(&psmPathInformation, 0, sizeof(ScePssFileInformation_t));


		strncpy(psmPathInformation.szName, setName.c_str(), PSM_PATH_MAX);
		psmPathInformation.uFileSize = stats.st_size;
		
		if (stats.st_ctime != -1)
			psmPathInformation.tCreationTime = stats.st_ctime;
		else
			psmPathInformation.tCreationTime = std::time(0);

		psmPathInformation.tLastWriteTime = stats.st_mtime;
		psmPathInformation.tLastAccessTime = stats.st_atime;

		if (this->IsDirectory(sandboxedPath))
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_DIRECTORY;

		if (((stats.st_mode & S_IREAD) != 0 && (stats.st_mode & S_IWRITE) == 0) || !filesystem->IsRewitable())
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_READONLY;

		//if (filesystem->IsEncrypted())
		//	psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_ENCRYPTED;


		return psmPathInformation;
	}

	bool Sandbox::IsFileSystemRootDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		for (FileSystem* filesystem : this->filesystems) {
			if (Shared::String::StringUtil::ToLower(absPath) == Shared::String::StringUtil::ToLower(filesystem->SandboxPath())) {
				return true;
			}
		}

		return false;
	}

	bool Sandbox::PathExist(std::string sandboxedPath, bool includeSystem) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (this->IsFileSystemRootDirectory(absPath))
			return true;

		if (this->findFilesystem(absPath, includeSystem) == NULL)
			return false;

		if (std::filesystem::exists(LocateRealPath(absPath, includeSystem)))
			return true;

		return false;
	}

	bool Sandbox::IsFile(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (!this->PathExist(absPath, false))
			return false;

		if (!this->IsDirectory(absPath))
			return true;

		return false;
	}

	bool Sandbox::IsDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (this->IsFileSystemRootDirectory(absPath))
			return true;

		if (!this->PathExist(absPath, false))
			return false;

		std::string realPath = this->LocateRealPath(absPath, false);

		if (std::filesystem::is_directory(realPath))
			return true;

		if (std::filesystem::is_regular_file(realPath))
			return false;

		return false;
	}

	void Sandbox::CloseDirectory(PsmFileDescriptor* handle) {
		if (handle != NULL) {
			if (handle->opened && handle->directoryFd != NULL) {
				delete handle->directoryFd;
			}
			handle->opened = false;
			delete handle;
		}
	}

	int Sandbox::ChangeSize(PsmFileDescriptor* handle, size_t newSize) {
		if (!handle->encrypted && handle->rw) { // Check the file is writable.

			// close becuase you cant resize the file while its open
			handle->edataStream->Close();

			// Resize the file to new size ...
			std::filesystem::resize_file(std::filesystem::path(handle->realPath), newSize);
			
			// open file again, at same position.
			this->reopen(handle); 

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_ACCESS_DENIED;
	}

	void Sandbox::CloseFile(PsmFileDescriptor* handle) {
		if (handle != NULL) {
			if (handle->opened && handle->edataStream != NULL) {
				delete handle->edataStream;
			}
			handle->opened = false;
			delete handle;
		}
	}

	size_t Sandbox::GetSize(PsmFileDescriptor* handle) {
		return handle->edataStream->Filesize();
	}

	PsmFileDescriptor* Sandbox::OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags, bool includeSystem) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		
		std::string realPath = this->LocateRealPath(absPath, includeSystem);
		FileSystem* filesystem = this->findFilesystem(absPath, includeSystem);


		PsmFileDescriptor* handle = new PsmFileDescriptor();

		// Are we trying to open a file for writing?
		bool openRw = (((flags & SCE_PSS_FILE_OPEN_FLAG_WRITE) != 0) || ((flags & SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE) != 0) || ((flags & SCE_PSS_FILE_OPEN_FLAG_APPEND) != 0));

		handle->realPath = realPath;
		handle->sandboxPath = absPath;

		handle->flags = flags;
		handle->rw = openRw;

		handle->directory = false;
		handle->directoryFd = NULL;

		if (openRw && !filesystem->IsRewitable()) {
			handle->opened = false;
			handle->failReason = PSM_ERROR_ACCESS_DENIED;
			return handle;
		}

		// Calculate mode

		std::fstream::ios_base::openmode openmode = 0;


		if ((flags & SCE_PSS_FILE_OPEN_FLAG_READ) != 0) {
			openmode |= std::ios::in;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_WRITE) != 0) {
			openmode |= std::ios::out;

			openmode |= std::ios::_Nocreate;
			openmode |= std::ios::trunc;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_BINARY) != 0) {
			openmode |= std::ios::binary;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_TEXT) != 0) {
			openmode &= std::ios::binary;
		}
		if ((flags & SCE_PSS_FILE_OPEN_FLAG_APPEND) != 0) {
			openmode |= std::ios::ate;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_NOREPLACE) != 0) {
			openmode |= std::ios::_Noreplace;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE) != 0) {
			openmode &= ~std::ios::_Nocreate;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE) != 0) {
			openmode &= ~std::ios::trunc;
		}
	
		handle->iflags = openmode;

		EdataStream* str = new EdataStream(realPath, openmode, this->GameDrmProvider);
		if (str->GetError() == PSM_ERROR_NO_ERROR) {
			handle->failReason = PSM_ERROR_NO_ERROR;
			handle->opened = true;
			handle->edataStream = str;
		}
		else {
			handle->failReason = str->GetError();
			delete str;
		}

		return handle;
	}

	int Sandbox::CopyFile(std::string sandboxedSrcPath, std::string sandboxDstPath, bool move) {
		// Find src and dest absoulte paths
		std::string absSrc = this->AbsolutePath(sandboxedSrcPath);
		std::string absDst = this->AbsolutePath(sandboxDstPath);

		// Find src and dest filesystem
		FileSystem* srcFilesystem = this->findFilesystem(absSrc, false);
		FileSystem* dstFilesystem = this->findFilesystem(absDst, false);

		// Check if src filesystem is read only- and this is a move
		if (srcFilesystem->IsEmulated() || !srcFilesystem->IsRewitable() && move)
			return PSM_ERROR_ACCESS_DENIED;

		// Check if dst filesystem is read only-
		if (dstFilesystem->IsEmulated() || !dstFilesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;

		// Check if either dst or src is a directory.
		if (this->IsDirectory(absSrc) || this->IsDirectory(absDst))
			return PSM_ERROR_FILE_NOT_FOUND;

		// Crate the directory if it does not exist.
		std::string parentDirectory = Shared::String::Path::UpDirectory(sandboxDstPath);
		if (!this->PathExist(parentDirectory, false))
			this->CreateDirectory(parentDirectory);

		// Locate real location of src and dst.
		std::string realSrc = this->LocateRealPath(absSrc, false);
		std::string realDst = this->LocateRealPath(absDst, false);

		if (move) { // Move operation? simply "rename" the file to new location
			std::filesystem::rename(realSrc, realDst);
			return PSM_ERROR_NO_ERROR;
		}
		else { // This is a copy operation.. 
			const int totalReadAtOnce = 0x80000;
			char* buffer = new char[totalReadAtOnce];

			PsmFileDescriptor* srcHandle = this->OpenFile(absSrc, (ScePssFileOpenFlag_t)(SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE | SCE_PSS_FILE_OPEN_FLAG_NOREPLACE), false);
			PsmFileDescriptor* dstHandle = this->OpenFile(absDst, (ScePssFileOpenFlag_t)(SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_WRITE | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE), false);
			this->ChangeSize(dstHandle, 0);
				
			int totalRead = 0;
			do {
				totalRead = this->ReadFile(srcHandle, totalReadAtOnce, buffer);
				this->WriteFile(dstHandle, totalRead, buffer);
			} while (totalRead != 0);
				
			this->CloseFile(srcHandle);
			this->CloseFile(dstHandle);

			delete[] buffer;
			return PSM_ERROR_NO_ERROR;
		}

	}

	int Sandbox::SetAttributes(std::string sandboxedPath, uint32_t attributes) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		FileSystem* filesystem = this->findFilesystem(absPath, false);

		if (filesystem->IsEmulated())
			return PSM_ERROR_ACCESS_DENIED;
		if (!filesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;
		
		if (this->IsDirectory(absPath))
			return PSM_ERROR_NOT_FOUND;

		if (!this->PathExist(absPath, false))
			return PSM_ERROR_NOT_FOUND;

		std::string realPath = this->LocateRealPath(absPath, false);
		
		return PlatformSpecific::ChangeFileAttributes(realPath, attributes);
	}


	int Sandbox::SetFileTimes(std::string sandboxedPath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime) {
		// Get absoulte path of file
		std::string absPath = this->AbsolutePath(sandboxedPath);

		// Determine filesystem its located in
		FileSystem* filesystem = this->findFilesystem(absPath, false);

		// Check if exists
		if (!this->PathExist(absPath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		// Check if is exactly an emulated directory.
		if (this->IsFileSystemRootDirectory(absPath))
			return PSM_ERROR_PATH_NOT_FOUND;

		// Check if emulated dir
		if (filesystem->IsEmulated())
			return PSM_ERROR_ACCESS_DENIED;
		// Check if dir is writable
		if (!filesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;


		ScePssFileInformation_t fileInfo = this->Stat(absPath, absPath);

		if (CreationTime == -1)
			CreationTime = fileInfo.tCreationTime;
		if (LastAccessTime == -1)
			LastAccessTime = fileInfo.tLastAccessTime;
		if (LastWriteTime == -1)
			LastWriteTime = fileInfo.tLastWriteTime;

		std::string realPath = this->LocateRealPath(absPath, false);


		// Use OS Specific API to change file times
		return PlatformSpecific::ChangeFileTimes(realPath, CreationTime, LastAccessTime, LastWriteTime);
	}

	int Sandbox::FlushFile(PsmFileDescriptor* handle) {
		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->rw || handle->encrypted || handle->emulated)
			return PSM_ERROR_ACCESS_DENIED;

		if (handle->edataStream == NULL)
			return PSM_ERROR_INVALID_HANDLE;

		handle->edataStream->Flush();
		return PSM_ERROR_NO_ERROR;
	}

	size_t Sandbox::WriteFile(PsmFileDescriptor* handle, size_t numbBytes, char* buffer) {
		if (!handle->encrypted && handle->rw) {
			return handle->edataStream->Write(buffer, numbBytes);
		}
		return PSM_ERROR_WRITE_FAILED;
	}

	int Sandbox::DeleteDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		// Check the path is inside a rewritable filesystem.
		FileSystem* filesystem = this->findFilesystem(absPath, false);
		if (!filesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;

		// Check the path is an actual directory, and that exists 
		if (!this->IsDirectory(absPath) || !this->PathExist(absPath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		// Locate the directory on disk and delete it
		std::string realPath = this->LocateRealPath(absPath, false);
		try{
			std::filesystem::remove(realPath);
		}
		catch (std::filesystem::filesystem_error) {
			return PSM_ERROR_ERROR;
		}
		
		return PSM_ERROR_NO_ERROR;

	}

	int Sandbox::CreateDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		// Return success if directory already exists.
		if (this->IsDirectory(absPath))
			return PSM_ERROR_NO_ERROR;

		// Check the path is inside a rewritable filesystem
		FileSystem* filesystem = this->findFilesystem(absPath, false);

		if (!filesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;
		
		// Check the path does not already contain a file.
		if (this->IsFile(absPath))
			return PSM_ERROR_ALREADY_EXISTS;

		// Locate path on disk, and create directores
		std::string realPath = this->LocateRealPath(absPath, false);
		std::filesystem::create_directories(realPath);

		return PSM_ERROR_NO_ERROR;

	}

	int Sandbox::SetCurrentDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (!this->PathExist(absPath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		if (this->IsFile(absPath))
			return PSM_ERROR_PATH_NOT_FOUND;

		this->currentWorkingDirectory = absPath;

		return PSM_ERROR_NO_ERROR;
	}

	std::string Sandbox::GetCurrentDirectory() {
		return this->currentWorkingDirectory;
	}

	int Sandbox::DeleteFile(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		// Check that the file actually exists,
		if (!this->PathExist(absPath, false) || this->IsDirectory(absPath))
			return PSM_ERROR_FILE_NOT_FOUND;
		
		// Check that the file is not in a read-only folder
		FileSystem* filesystem = this->findFilesystem(absPath, false);
		if (!filesystem->IsRewitable() || filesystem->IsEmulated())
			return PSM_ERROR_ACCESS_DENIED;

		// Locate the file on disk, and delete it
		std::string realPath = this->LocateRealPath(absPath, false);
		std::filesystem::remove(std::filesystem::path(realPath));

		return PSM_ERROR_NO_ERROR;
	}

	int Sandbox::Seek(PsmFileDescriptor* handle, uint32_t offset, ScePssFileSeekType_t seekType) {
		return handle->edataStream->Seek(offset, seekType);
	}

	PsmFileDescriptor* Sandbox::OpenDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		std::string realPath = this->LocateRealPath(absPath, false);
		FileSystem* filesystem = this->findFilesystem(absPath, false);

		// Create a new PsmFileDescriptor 
		PsmFileDescriptor* handle = new PsmFileDescriptor();

		// Fail if its a file or it doesnt exist.
		if (this->IsFile(absPath) || !this->PathExist(absPath, false)) {
			handle->failReason = PSM_ERROR_PATH_NOT_FOUND;
			return handle;
		}

		// Setup handle struct
		handle->opened = true;
		handle->rw = filesystem->IsRewitable();
		handle->encrypted = false;
		handle->emulated = filesystem->IsEmulated();
		handle->directory = true;

		handle->flags = SCE_PSS_FILE_OPEN_FLAG_READ;
		handle->sandboxPath = absPath;
		handle->realPath = realPath;

		if (!handle->emulated)
			handle->directoryFd = new DirectoryIterator(absPath, false);
		else
			handle->directoryFd = nullptr;
		
		handle->edataStream = nullptr;

		// Set fail reason to no error, and return
		handle->failReason = PSM_ERROR_NO_ERROR;
		return handle;
	}

	std::string Sandbox::LocateRealPath(std::string sandboxedPath, bool includeSystem) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		
		// find what filesystem the path is located in, (eg /Application) 
		FileSystem* filesystem = this->findFilesystem(sandboxedPath, includeSystem);

		// Get the real path to this folder on disk
		std::filesystem::path fsRealPath = std::filesystem::path(filesystem->PathOnDisk());
		
		// Get the folder name inside the PSM Sandbox.
		std::string fsName = filesystem->SandboxPath();

		if (!this->IsFileSystemRootDirectory(absPath)) {
			// Subtract sandbox name from the full path, should result in a relative path from inside the specific sandboxed folder ..
			std::string pathRelativeToFilesystem = absPath.substr(fsName.length() + 1);

			// Append that file path to real path,
			fsRealPath.append(pathRelativeToFilesystem);
		}


		// Swap slahses to the format used by the current Operating System,
		std::string outPath = fsRealPath.string();
		outPath = Shared::String::Path::ChangeSlashesToNativeStyle(outPath);

		return outPath;
	}

	std::string Sandbox::AbsolutePath(std::string sandboxedPath) {
		std::vector<std::string> absolutePathComponents;
		
		// Limit str to PSM_PATH_MAX.
		sandboxedPath = sandboxedPath.substr(0, PSM_PATH_MAX);

		std::string startDir = Sandbox::currentWorkingDirectory;

		// Check if string starts with a /, and act as though the working direcory is the root
		if (sandboxedPath.length() >= 1 && sandboxedPath[0] == '/')
			startDir = "";

		// Split path by the / seperator
		std::vector<std::string> pathComponents = Shared::String::StringUtil::Split(Shared::String::Path::ChangeSlashesToPsmStyle(sandboxedPath), PSM_PATH_SEPERATOR);

		// if you think about it, file paths are essentially. just First-In-First-Out much like The Stack,

		for (std::string pathComponent : pathComponents) {
			if (pathComponent == ".") { // . indicates the current directory, so just nop
				continue;
			}
			else if (pathComponent == "..") { // .. indicates to go back one directory, basically, pop
				if (absolutePathComponents.size() >= 1)
					absolutePathComponents.pop_back();
				continue;
			}
			else { // everything else is actually part of the path, basically push
				absolutePathComponents.push_back(pathComponent);
			}
		}

		std::string absolutePath = startDir + Shared::String::StringUtil::Join(absolutePathComponents, PSM_PATH_SEPERATOR);
		return absolutePath;
	}

}