#include <IO/Sandbox.hpp>
#include <IO/Path.hpp>
#include <Util/StringUtils.hpp>
#include <filesystem>
#include <sys/stat.h>
#include <mono/mono.h>
#include <LibPSM.hpp>
#include <Runtime/AppGlobals.hpp>
#include <Debug/Logger.hpp>
#include <IO/PlatformSpecific.hpp>

using namespace SnowPME::Util;
using namespace SnowPME::Debug;
namespace SnowPME::IO {


	Sandbox::Sandbox(std::string gameFolder) {
		std::filesystem::path gamePath = std::filesystem::path(gameFolder);
		std::filesystem::path applicationPath = std::filesystem::path(gameFolder).append("Application");
		std::filesystem::path documentsPath = std::filesystem::path(gameFolder).append("Documents");
		std::filesystem::path tempPath = std::filesystem::path(gameFolder).append("Temp");

		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(applicationPath).string(), "/Application", false, false));
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(tempPath).string(), "/Temp", true, false));
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(documentsPath).string(), "/Documents", true, false));

		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(gamePath).string(), "/", false, true));

		this->currentWorkingDirectory = "/";

	}
	Sandbox::~Sandbox() {
		// Iterate over all fileystems
		for (FileSystem* filesystem : this->filesystems) {
			delete filesystem; // delete the filesystem
		}

		Sandbox::filesystems.clear(); // Clear the filesystems vector
	}
	
	// Some functions require handling via filepath,
	// in these cases, the fstream needs to be created again
	void Sandbox::reopen(PsmHandle* handle) {
		if (handle->opened && !handle->directory && handle->fileFd != NULL) {
			// Close the file
			if(handle->fileFd->is_open())
				handle->fileFd->close();
			delete handle->fileFd;

			// Open the file again
			std::fstream* str = new std::fstream();
			str->open(handle->realPath, handle->iflags);

			// Seek to where we were.
			str->seekg(handle->seekPos, std::ios::beg);
			
			// Overwrite the fstream.
			handle->fileFd = str;
		}
	}

	// Determines which "FileSystem" a given file is in,
	// eg /Application or /Documents, 
	FileSystem* Sandbox::findFilesystem(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		for (FileSystem* filesystem : Sandbox::filesystems) {
			if (StringUtils::ToLower(absPath).starts_with(StringUtils::ToLower(filesystem->SandboxPath()))) {
				return filesystem;
			}
		}

		throw std::exception("FileSystem not found ?? ??");
	}

	size_t Sandbox::ReadFile(PsmHandle* handle, size_t numbBytes, char* buffer) {
		if (!handle->encrypted) {
			handle->fileFd->read(buffer, numbBytes);
			size_t bytesRead = (size_t)handle->fileFd->gcount();
			handle->seekPos += bytesRead;
			return bytesRead;
		}

		throw std::exception("Encryption not yet implemented. ?? ??");
	}

	int Sandbox::ReadDirectory(PsmHandle* handle, ScePssFileInformation_t* fileInfo) {

		memset(fileInfo, 0, sizeof(ScePssFileInformation_t));

		if (handle->emulated) { // handle "/" emulated directory, display all sandboxed paths
			if (handle->seekPos >= this->filesystems.size()) {
				return PSM_ERROR_PATH_NOT_FOUND;
			}
			else {

				FileSystem* filesystem = this->filesystems[handle->seekPos];
				handle->seekPos++;

				if (filesystem->IsEmulated()) // look okay, / has crippling dysphoria, xe dont need to show xerself.
					return this->ReadDirectory(handle, fileInfo);

				std::string filename = Path::GetFilename(filesystem->SandboxPath());

				ScePssFileInformation_t psmPathInformation = this->Stat(filesystem->SandboxPath(), filename);
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

			handle->seekPos++;
			return PSM_ERROR_NO_ERROR;
		}
	}

	ScePssFileInformation_t Sandbox::Stat(std::string sandboxedPath, std::string setName) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		FileSystem* filesystem = this->findFilesystem(sandboxedPath);

		struct stat stats;
		stat(this->LocateRealPath(absPath).c_str(), &stats);

		ScePssFileInformation_t psmPathInformation;
		memset(&psmPathInformation, 0, sizeof(ScePssFileInformation_t));

		strncpy(psmPathInformation.szName, setName.c_str(), PSM_PATH_MAX);
		psmPathInformation.uFileSize = stats.st_size;
		psmPathInformation.tCreationTime = stats.st_ctime;
		psmPathInformation.tLastWriteTime = stats.st_mtime;
		psmPathInformation.tLastAccessTime = stats.st_atime;

		if (this->IsDirectory(sandboxedPath))
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_DIRECTORY;

		if (((stats.st_mode & S_IREAD) != 0 && (stats.st_mode & S_IWRITE) == 0) || !filesystem->IsRewitable())
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_READONLY;

		if (filesystem->IsEncrypted())
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_ENCRYPTED;


		return psmPathInformation;
	}

	bool Sandbox::IsFileSystemRootDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		for (FileSystem* filesystem : this->filesystems) {
			if (StringUtils::ToLower(absPath) == StringUtils::ToLower(filesystem->SandboxPath())) {
				return true;
			}
		}

		return false;
	}

	bool Sandbox::PathExist(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (this->IsFileSystemRootDirectory(absPath))
			return true;

		if (this->findFilesystem(absPath) == NULL)
			return false;

		if (std::filesystem::exists(LocateRealPath(absPath)))
			return true;

		return false;
	}

	bool Sandbox::IsFile(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (!this->PathExist(absPath))
			return false;

		if (!this->IsDirectory(absPath))
			return true;

		return false;
	}

	bool Sandbox::IsDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (this->IsFileSystemRootDirectory(absPath))
			return true;

		if (!this->PathExist(absPath))
			return false;

		std::string realPath = this->LocateRealPath(absPath);

		if (std::filesystem::is_directory(realPath))
			return true;

		if (std::filesystem::is_regular_file(realPath))
			return false;

		return false;
	}

	void Sandbox::CloseDirectory(PsmHandle* handle) {
		if (handle != NULL) {
			if (handle->opened && handle->directoryFd != NULL) {
				delete handle->directoryFd;
			}
			handle->opened = false;
			delete handle;
		}
	}

	int Sandbox::ChangeSize(PsmHandle* handle, size_t newSize) {
		if (!handle->encrypted && handle->rw) { // Workaround fstream stupidity.
			// close becuase you cant resize the file while its open
			handle->fileFd->close();

			// Resize the file to new size ...
			std::filesystem::resize_file(std::filesystem::path(handle->realPath), newSize);
			
			// open file again, at same position.
			this->reopen(handle); 

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_ACCESS_DENIED;
	}

	void Sandbox::CloseFile(PsmHandle* handle) {
		if (handle != NULL) {
			if (handle->opened && handle->fileFd != NULL) {
				handle->fileFd->close();
				delete handle->fileFd;
			}
			handle->opened = false;
			delete handle;
		}
	}

	size_t Sandbox::GetSize(PsmHandle* handle) {
		if (!handle->encrypted && !handle->directory) {
			size_t fileSize = (size_t)std::filesystem::file_size(handle->realPath);
			return fileSize;
		}
		throw std::exception("Encryption not implemented");
	}

	PsmHandle* Sandbox::OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		std::string realPath = this->LocateRealPath(absPath);

		FileSystem* filesystem = this->findFilesystem(absPath);

		PsmHandle* handle = new PsmHandle();

		// Are we trying to open a file for writing?
		bool openRw = (((flags & SCE_PSS_FILE_OPEN_FLAG_WRITE) != 0) || ((flags & SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE) != 0) || ((flags & SCE_PSS_FILE_OPEN_FLAG_APPEND) != 0));

		handle->realPath = realPath;
		handle->sandboxPath = absPath;

		handle->flags = flags;
		handle->rw = openRw;

		handle->directory = false;
		handle->directoryFd = NULL;


		if (filesystem->IsEncrypted()) {
			// TODO: check psse.list
			handle->encrypted = true;
		}

		if (openRw && !filesystem->IsRewitable()) {
			handle->opened = false;
			handle->failReason = PSM_ERROR_ACCESS_DENIED;
			return handle;
		}

		// Calculate mode

		std::fstream::ios_base::openmode openmode = 0;
		openmode |= std::ios::_Nocreate;
		openmode |= std::ios::trunc;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_READ) != 0)
			openmode |= std::ios::in;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_WRITE) != 0)
			openmode |= std::ios::out;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_BINARY) != 0)
			openmode |= std::ios::binary;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_TEXT) != 0)
			openmode &= std::ios::binary;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_APPEND) != 0)
			openmode |= std::ios::app;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_NOREPLACE) != 0)
			openmode |= std::ios::_Noreplace;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE) != 0)
			openmode &= ~std::ios::_Nocreate;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE) != 0)
			openmode &= ~std::ios::trunc;

		handle->iflags = openmode;

		std::fstream* str = new std::fstream();
		str->open(realPath, openmode);

		handle->failReason = PSM_ERROR_NO_ERROR;
		handle->opened = true;
		handle->fileFd = str;

		return handle;
	}

	int Sandbox::CopyFile(std::string sandboxedSrcPath, std::string sandboxDstPath, bool move) {
		// Find src and dest absoulte paths
		std::string absSrc = this->AbsolutePath(sandboxedSrcPath);
		std::string absDst = this->AbsolutePath(sandboxDstPath);

		// Find src and dest filesystem
		FileSystem* srcFilesystem = this->findFilesystem(absSrc);
		FileSystem* dstFilesystem = this->findFilesystem(absDst);

		// Check if src filesystem is read only- and this is a move
		if (srcFilesystem->IsEmulated() || srcFilesystem->IsEncrypted() && move)
			return PSM_ERROR_ACCESS_DENIED;

		// Check if dst filesystem is read only-
		if (dstFilesystem->IsEmulated() || dstFilesystem->IsEncrypted() || !dstFilesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;

		// Check if either dst or src is a directory.
		if (this->IsDirectory(absSrc) || this->IsDirectory(absDst))
			return PSM_ERROR_FILE_NOT_FOUND;

		// Crate the directory if it does not exist.
		std::string parentDirectory = Path::UpDirectory(sandboxDstPath);
		if (!this->PathExist(parentDirectory))
			this->CreateDirectory(parentDirectory);

		// Locate real location of src and dst.
		std::string realSrc = this->LocateRealPath(absSrc);
		std::string realDst = this->LocateRealPath(absDst);

		if (move) { // Move operation? simply "rename" the file to new location
			std::filesystem::rename(realSrc, realDst);
			return PSM_ERROR_NO_ERROR;
		}
		else { // This is a copy operation.. 
			const int totalReadAtOnce = 0x80000;
			char* buffer = new char[totalReadAtOnce];

			PsmHandle* srcHandle = this->OpenFile(absSrc, (ScePssFileOpenFlag_t)(SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE | SCE_PSS_FILE_OPEN_FLAG_NOREPLACE));
			PsmHandle* dstHandle = this->OpenFile(absDst, (ScePssFileOpenFlag_t)(SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_WRITE | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE));
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

		FileSystem* filesystem = this->findFilesystem(absPath);

		if (filesystem->IsEmulated())
			return PSM_ERROR_ACCESS_DENIED;
		if (!filesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;
		
		if (this->IsDirectory(absPath))
			return PSM_ERROR_NOT_FOUND;

		if (!this->PathExist(absPath))
			return PSM_ERROR_NOT_FOUND;

		std::string realPath = this->LocateRealPath(absPath);
		
		return PlatformSpecific::ChangeFileAttributes(realPath, attributes);
	}


	int Sandbox::SetFileTimes(std::string sandboxedPath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime) {
		// Get absoulte path of file
		std::string absPath = this->AbsolutePath(sandboxedPath);

		// Determine filesystem its located in
		FileSystem* filesystem = this->findFilesystem(absPath);

		// Check if exists
		if (!this->PathExist(absPath))
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

		std::string realPath = this->LocateRealPath(absPath);


		// Use OS Specific API to change file times
		return PlatformSpecific::ChangeFileTimes(realPath, CreationTime, LastAccessTime, LastWriteTime);
	}

	int Sandbox::FlushFile(PsmHandle* handle) {
		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->rw || handle->encrypted || handle->emulated)
			return PSM_ERROR_ACCESS_DENIED;

		if (handle->fileFd == NULL)
			return PSM_ERROR_INVALID_HANDLE;

		handle->fileFd->flush();
		return PSM_ERROR_NO_ERROR;
	}

	size_t Sandbox::WriteFile(PsmHandle* handle, size_t numbBytes, char* buffer) {
		if (!handle->encrypted && handle->rw) {

			// Write buffer to file
			handle->fileFd->write(buffer, numbBytes);

			// fstream provides no way of knowing how many bytes were actually written
			// So just pray and hope;

			// Update the seek position by how many bytes written
			handle->seekPos += numbBytes;

			return numbBytes;
		}
		throw std::exception("Tried to write to encrypted file?");
	}

	int Sandbox::DeleteDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		// Check the path is inside a rewritable filesystem.
		FileSystem* filesystem = this->findFilesystem(absPath);
		if (!filesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;

		// Check the path is an actual directory, and that exists 
		if (!this->IsDirectory(absPath) || !this->PathExist(absPath))
			return PSM_ERROR_PATH_NOT_FOUND;

		// Locate the directory on disk and delete it
		std::string realPath = this->LocateRealPath(absPath);
		std::filesystem::remove(realPath);

		return PSM_ERROR_NO_ERROR;

	}

	int Sandbox::CreateDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		// Check the path is inside a rewritable filesystem
		FileSystem* filesystem = this->findFilesystem(absPath);
		if (!filesystem->IsRewitable())
			return PSM_ERROR_ACCESS_DENIED;
		
		// Check the path does not already contain a file.
		if (this->IsFile(absPath))
			return PSM_ERROR_ALREADY_EXISTS;

		// Locate path on disk, and create directores
		std::string realPath = this->LocateRealPath(absPath);
		std::filesystem::create_directories(realPath);

		return PSM_ERROR_NO_ERROR;

	}

	int Sandbox::SetCurrentDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		if (!this->PathExist(absPath))
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
		if (!this->PathExist(absPath) || this->IsDirectory(absPath))
			return PSM_ERROR_FILE_NOT_FOUND;
		
		// Check that the file is not in a read-only folder
		FileSystem* filesystem = this->findFilesystem(absPath);
		if (!filesystem->IsRewitable() || filesystem->IsEmulated())
			return PSM_ERROR_ACCESS_DENIED;

		// Locate the file on disk, and delete it
		std::string realPath = this->LocateRealPath(absPath);
		std::filesystem::remove(std::filesystem::path(realPath));

		return PSM_ERROR_NO_ERROR;
	}

	int Sandbox::Seek(PsmHandle* handle, uint32_t offset, ScePssFileSeekType_t seekType) {
		if (!handle->encrypted) {

			// Translate seek command to native one.
			size_t totalFileSz = this->GetSize(handle);
			switch (seekType) {
			case SCE_PSS_FILE_SEEK_TYPE_BEGIN:
				handle->seekPos = offset;
				handle->fileFd->seekg(offset, std::ios::beg);
				break;
			case SCE_PSS_FILE_SEEK_TYPE_CURRENT:
				handle->seekPos += offset;
				handle->fileFd->seekg(offset, std::ios::cur);
				break;
			case SCE_PSS_FILE_SEEK_TYPE_END:
				handle->seekPos = totalFileSz - offset;
				handle->fileFd->seekg(offset, std::ios::end);
				break;
			default:
				return PSM_ERROR_ERROR;
			}

			if (handle->seekPos > totalFileSz)
				handle->seekPos = totalFileSz;

			if (handle->seekPos < 0)
				handle->seekPos = 0;

			return PSM_ERROR_NO_ERROR;

		}
		throw new std::exception("encryption not implemented!");
	}

	PsmHandle* Sandbox::OpenDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		std::string realPath = this->LocateRealPath(absPath);
		FileSystem* filesystem = this->findFilesystem(absPath);

		// Create a new PsmHandle 
		PsmHandle* handle = new PsmHandle();

		// Fail if its a file or it doesnt exist.
		if (this->IsFile(absPath) || !this->PathExist(absPath)) {
			handle->failReason = PSM_ERROR_PATH_NOT_FOUND;
			return handle;
		}

		// Setup handle struct
		handle->opened = true;
		handle->rw = filesystem->IsRewitable();
		handle->encrypted = filesystem->IsEncrypted();
		handle->emulated = filesystem->IsEmulated();
		handle->directory = true;

		handle->flags = SCE_PSS_FILE_OPEN_FLAG_READ;
		handle->sandboxPath = absPath;
		handle->realPath = realPath;

		if (!handle->emulated)
			handle->directoryFd = new DirectoryIterator(absPath, false);
		else
			handle->directoryFd = NULL;
		
		handle->fileFd = NULL;

		// Set fail reason to no error, and return
		handle->failReason = PSM_ERROR_NO_ERROR;
		return handle;
	}
	std::string Sandbox::LocateRealPath(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		
		// find what filesystem the path is located in, (eg /Application) 
		FileSystem* filesystem = this->findFilesystem(sandboxedPath);

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

		return fsRealPath.string();
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
		std::vector<std::string> pathComponents = StringUtils::Split(Path::ChangeSlashesToPsmStyle(sandboxedPath), PSM_PATH_SEPERATOR);

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

		std::string absolutePath = startDir + StringUtils::Join(absolutePathComponents, PSM_PATH_SEPERATOR);
		return absolutePath;
	}

}