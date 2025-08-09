#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Io/PsmFileHandle.hpp>
#include <Sce/Pss/Core/Io/EmulatedDirectory.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataStream.hpp>

#include <filesystem>
#include <sys/stat.h>
#include <mono/mono.h>

#include <LibShared.hpp>

using namespace Shared;
using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Io::Edata;

namespace Sce::Pss::Core::Io {

	Sandbox::Sandbox(std::string gameFolder) {

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

		if (Config::TargetImplementation == RuntimeImplementation::PSVita && std::filesystem::exists(roPath))
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

		this->filesystems.push_back(FileSystem(std::filesystem::absolute(applicationPath).string(), "/Application", false, false, false));
		this->filesystems.push_back(FileSystem(std::filesystem::absolute(tempPath).string(), "/Temp", true, false, false));
		this->filesystems.push_back(FileSystem(std::filesystem::absolute(documentsPath).string(), "/Documents", true, false, false));

		// system directories
		this->filesystems.push_back(FileSystem(std::filesystem::absolute(licensePath).string(), "/License", false, false, true));
		this->filesystems.push_back(FileSystem(std::filesystem::absolute(systemPath).string(), "/System", true, false, true));
		
		// the last "/" filesystem, listing all the others;
		this->filesystems.push_back(FileSystem(std::filesystem::absolute(systemPath).string(), "/", false, true, false));


		this->readLicenseData();
	}

	std::string Sandbox::normalizePath(std::string sandboxedPath) {
		// Limit str to PSM_PATH_MAX.
		sandboxedPath = sandboxedPath.substr(0, PSM_PATH_MAX);

		std::string startDir = this->GetWorkingDirectory();

		return Path::NormalizePath(startDir, sandboxedPath);
	}
	int Sandbox::readLicenseData() {
		if (this->PathExist(FakeRifLocation, true)) {
			this->GameDrmProvider = new PsmDrm(FakeRifLocation);
			RETURN_ERRORABLE(this->GameDrmProvider);
		}
		else {
			Logger::Warn("No " + FakeRifLocation + " found. - This is normal if your running a pre-decrypted executable (i.e homebrew)");
		}
		return PSM_ERROR_NO_ERROR;
	}

	Sandbox::~Sandbox() {
		if (this->GameDrmProvider != nullptr) // delete game drm provider
			delete this->GameDrmProvider;

		this->filesystems.clear(); // Clear the filesystems vector
	}
	
	// Some functions require handling via filepath,
	// in these cases, the fstream needs to be created again
	void Sandbox::reopen(std::shared_ptr<PsmFileHandle> handle) {
		if (handle->IsOpen() && !handle->IsDirectory() && handle->GetUnderlying() != nullptr) {
			// Close the file
			EdataStream* edataStream = static_cast<EdataStream*>(handle->GetUnderlying());
			uint64_t oldPos = edataStream->Tell();
			EdataList* edataList = edataStream->EncryptedDataList;
			delete edataStream;

			// Open the file again
			handle->SetUnderyling(new EdataStream(handle->PathOnDisk(), handle->OpenMode(), this->GameDrmProvider, edataList));

			// Seek to where we were.
			static_cast<EdataStream*>(handle->GetUnderlying())->Seek(oldPos, SCE_PSS_FILE_SEEK_TYPE_BEGIN);
		}
	}

	// Determines which "FileSystem" a given file is in,
	// eg /Application or /Documents, 
	FileSystem Sandbox::findFilesystem(std::string sandboxedPath, bool includeSystem) {
		std::string normPath = this->normalizePath(sandboxedPath);

		for (FileSystem filesystem : this->filesystems) {
			if (String::Format::ToLower(normPath).starts_with(String::Format::ToLower(filesystem.SandboxPath()))) {
				if (filesystem.IsSystem() && !includeSystem) continue;

				return filesystem;
			}
		}

		PANIC(sandboxedPath + " was not part of any filesystem.");
		return this->filesystems.front();
	}


	ScePssFileInformation_t Sandbox::Stat(std::string sandboxedPath, std::string setName) {
		std::string normPath = this->normalizePath(sandboxedPath);
		std::string normSetNamePath = this->normalizePath(setName);

		FileSystem filesystem = this->findFilesystem(sandboxedPath, false);

		struct stat stats;
		stat(this->LocateRealPath(normPath, false).c_str(), &stats);

		ScePssFileInformation_t psmPathInformation;
		memset(&psmPathInformation, 0, sizeof(ScePssFileInformation_t));


		strncpy(psmPathInformation.szName, normSetNamePath.c_str(), PSM_PATH_MAX);
		psmPathInformation.uFileSize = stats.st_size;
		
		if (stats.st_ctime != -1)
			psmPathInformation.tCreationTime = stats.st_ctime;
		else
			psmPathInformation.tCreationTime = std::time(0);

		psmPathInformation.tLastWriteTime = stats.st_mtime;
		psmPathInformation.tLastAccessTime = stats.st_atime;

		if (this->IsDirectory(sandboxedPath))
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_DIRECTORY;

		if (((stats.st_mode & S_IREAD) != 0 && (stats.st_mode & S_IWRITE) == 0) || !filesystem.IsWritable())
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_READONLY;

		if (filesystem.GetEdataList(this->GameDrmProvider) != nullptr) {
			if (filesystem.GetEdataList(this->GameDrmProvider)->IsFileInEdata(normPath)) {
				psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_ENCRYPTED;
			}
		}

		return psmPathInformation;
	}

	bool Sandbox::IsFileSystemRootDirectory(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);

		for (FileSystem filesystem : this->filesystems) {
			if (Format::ToLower(normPath) == Format::ToLower(this->normalizePath(filesystem.SandboxPath()))) {
				return true;
			}
		}

		return false;
	}

	bool Sandbox::PathExist(std::string sandboxedPath, bool includeSystem) {
		std::string normPath = this->normalizePath(sandboxedPath);

		if (this->IsFileSystemRootDirectory(normPath))
			return true;

		if (this->findFilesystem(normPath, includeSystem).IsRoot())
			return false;

		if (std::filesystem::exists(LocateRealPath(normPath, includeSystem)))
			return true;

		return false;
	}

	bool Sandbox::IsFile(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);

		if (!this->PathExist(normPath, false))
			return false;

		if (!this->IsDirectory(normPath))
			return true;

		return false;
	}

	bool Sandbox::IsDirectory(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);

		if (this->IsFileSystemRootDirectory(normPath))
			return true;

		if (!this->PathExist(normPath, false))
			return false;

		std::string pathOnDisk = this->LocateRealPath(normPath, false);

		if (std::filesystem::is_directory(pathOnDisk))
			return true;

		if (std::filesystem::is_regular_file(pathOnDisk))
			return false;

		return false;
	}


	int Sandbox::ChangeSize(std::shared_ptr<PsmFileHandle> handle, uint32_t newSize) {
		if (!handle->IsEncrypted() && handle->IsRewritable()) { // Check the file is writable.

			// close becuase you cant resize the file while its open
			handle->GetUnderlying()->Close();

			// Resize the file to new size ...
			std::filesystem::resize_file(std::filesystem::path(handle->PathOnDisk()), newSize);
			
			// open file again, at same position.
			this->reopen(handle); 

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_ACCESS_DENIED;
	}

	std::shared_ptr<PsmFileHandle> Sandbox::OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags, bool includeSystem) {
		std::string pathInSandbox = this->normalizePath(sandboxedPath);
		std::string pathOnDisk = this->LocateRealPath(pathInSandbox, includeSystem);
		FileSystem filesystem = this->findFilesystem(pathInSandbox, includeSystem);

		// Create File Handle Object
		std::shared_ptr<PsmFileHandle> handle = PsmFileHandle::Create(pathInSandbox, pathOnDisk, flags);

		if (handle->IsRewritable() && !filesystem.IsWritable()) {
			handle->SetError(PSM_ERROR_ACCESS_DENIED);
			return handle;
		}

		// Calculate mode
		
		if (handle->IsRewritable()) {
			// handle ALWAYS_CREATE
			if ((handle->PssFlags() & SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE) == 0) {
				if (!this->PathExist(sandboxedPath, false)) {
					handle->SetError(PSM_ERROR_FILE_NOT_FOUND);
					return handle;
				}
			}

			// handle NOREPLACE
			if ((handle->PssFlags() & SCE_PSS_FILE_OPEN_FLAG_NOREPLACE) != 0) {
				if (this->PathExist(sandboxedPath, false)) {
					handle->SetError(PSM_ERROR_ALREADY_EXISTS);
					return handle;
				}
			}
		}

		handle->SetUnderyling(new EdataStream(handle->PathOnDisk(), handle->OpenMode(), this->GameDrmProvider, filesystem.GetEdataList(this->GameDrmProvider)));

		return handle;
	}

	int Sandbox::CopyFile(std::string sandboxedSrcPath, std::string sandboxDstPath, bool move) {
		// Find src and dest absoulte paths
		std::string normSrc = this->normalizePath(sandboxedSrcPath);
		std::string normDst = this->normalizePath(sandboxDstPath);

		// Find src and dest filesystem
		FileSystem srcFilesystem = this->findFilesystem(normSrc, false);
		FileSystem dstFilesystem = this->findFilesystem(normDst, false);
		
		// Check if src filesystem is the root filesystem
		if (srcFilesystem.IsRoot()) 
			return PSM_ERROR_ACCESS_DENIED;
		
		// Check if src filesystem is read only- and this is a move
		if (srcFilesystem.IsWritable() && move)
			return PSM_ERROR_ACCESS_DENIED;

		// Check if dst filesystem is read only-
		if (dstFilesystem.IsWritable())
			return PSM_ERROR_ACCESS_DENIED;

		// Check if either dst or src is a directory.
		if (this->IsDirectory(normSrc) || this->IsDirectory(normDst))
			return PSM_ERROR_FILE_NOT_FOUND;

		// Crate the directory if it does not exist.
		std::string parentDirectory = Shared::String::Path::UpDirectory(sandboxDstPath);
		if (!this->PathExist(parentDirectory, false))
			this->MakeDirectory(parentDirectory);

		// Locate real location of src and dst.
		std::string realSrc = this->LocateRealPath(normSrc, false);
		std::string realDst = this->LocateRealPath(normDst, false);

		if (move) { // Move operation? simply "rename" the file to new location
			std::filesystem::rename(realSrc, realDst);
			return PSM_ERROR_NO_ERROR;
		}
		else { // otherwise, its a copy operation..
			char buffer[0x8000];

			std::shared_ptr<PsmFileHandle> srcHandle = this->OpenFile(normSrc, (ScePssFileOpenFlag_t)(SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE | SCE_PSS_FILE_OPEN_FLAG_NOREPLACE), false);
			std::shared_ptr<PsmFileHandle> dstHandle = this->OpenFile(normDst, (ScePssFileOpenFlag_t)(SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_WRITE | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE), false);
			this->ChangeSize(dstHandle, 0);
				
			int totalRead = 0;
			do {
				totalRead = srcHandle->GetUnderlying()->Read(buffer, sizeof(buffer));
				static_cast<EdataStream*>(dstHandle->GetUnderlying())->Write(buffer, totalRead);
			} while (totalRead != 0);
				
			PsmFileHandle::Delete(srcHandle);
			PsmFileHandle::Delete(dstHandle);

			return PSM_ERROR_NO_ERROR;
		}

	}

	int Sandbox::SetAttributes(std::string sandboxedPath, uint32_t attributes) {
		std::string normPath = this->normalizePath(sandboxedPath);

		FileSystem filesystem = this->findFilesystem(normPath, false);

		if (filesystem.IsRoot())
			return PSM_ERROR_ACCESS_DENIED;

		if (!filesystem.IsWritable())
			return PSM_ERROR_ACCESS_DENIED;
		
		if (this->IsDirectory(normPath))
			return PSM_ERROR_NOT_FOUND;

		if (!this->PathExist(normPath, false))
			return PSM_ERROR_NOT_FOUND;

		std::string PathOnDisk = this->LocateRealPath(normPath, false);
		
		return PlatformSpecific::ChangeFileAttributes(PathOnDisk, attributes);
	}


	int Sandbox::SetFileTimes(std::string sandboxedPath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime) {
		std::string normPath = this->normalizePath(sandboxedPath);

		// Determine filesystem its located in
		FileSystem filesystem = this->findFilesystem(normPath, false);

		// Check if exists
		if (!this->PathExist(normPath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		// Check if is exactly an root directory.
		if (this->IsFileSystemRootDirectory(normPath))
			return PSM_ERROR_PATH_NOT_FOUND;

		// Check if dir is writable
		if (!filesystem.IsWritable())
			return PSM_ERROR_ACCESS_DENIED;

		ScePssFileInformation_t fileInfo = this->Stat(normPath, normPath);

		if (CreationTime == -1)
			CreationTime = fileInfo.tCreationTime;
		if (LastAccessTime == -1)
			LastAccessTime = fileInfo.tLastAccessTime;
		if (LastWriteTime == -1)
			LastWriteTime = fileInfo.tLastWriteTime;

		std::string PathOnDisk = this->LocateRealPath(normPath, false);

		// Use OS Specific API to change file times
		return PlatformSpecific::ChangeFileTimes(PathOnDisk, CreationTime, LastAccessTime, LastWriteTime);
	}

	int Sandbox::RemoveDirectory(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);
		// Check the path is inside a rewritable filesystem.
		FileSystem filesystem = this->findFilesystem(normPath, false);
		if (!filesystem.IsWritable())
			return PSM_ERROR_ACCESS_DENIED;

		// Check the path is an actual directory, and that exists 
		if (!this->IsDirectory(normPath) || !this->PathExist(normPath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		// Locate the directory on disk and delete it
		std::string PathOnDisk = this->LocateRealPath(normPath, false);
		if(!std::filesystem::remove(PathOnDisk)) return PSM_ERROR_ERROR;
		
		return PSM_ERROR_NO_ERROR;

	}

	int Sandbox::MakeDirectory(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);

		// Return success if directory already exists.
		if (this->IsDirectory(normPath))
			return PSM_ERROR_NO_ERROR;

		// Check the path is inside a rewritable filesystem
		FileSystem filesystem = this->findFilesystem(normPath, false);

		if (!filesystem.IsWritable())
			return PSM_ERROR_ACCESS_DENIED;
		
		// Check the path does not already contain a file.
		if (this->IsFile(normPath))
			return PSM_ERROR_ALREADY_EXISTS;

		// Locate path on disk, and create directores
		std::string PathOnDisk = this->LocateRealPath(normPath, false);
		std::filesystem::create_directories(PathOnDisk);

		return PSM_ERROR_NO_ERROR;

	}

	int Sandbox::SetWorkingDirectory(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);

		if (!this->PathExist(normPath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		if (this->IsFile(normPath))
			return PSM_ERROR_PATH_NOT_FOUND;

		this->currentWorkingDirectory = normPath;

		return PSM_ERROR_NO_ERROR;
	}

	std::string Sandbox::GetWorkingDirectory() {
		return this->currentWorkingDirectory;
	}

	int Sandbox::RemoveFile(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);

		// Check that the file actually exists,
		if (!this->PathExist(normPath, false) || this->IsDirectory(normPath))
			return PSM_ERROR_FILE_NOT_FOUND;
		
		// Check that the file is not in a read-only folder
		FileSystem filesystem = this->findFilesystem(normPath, false);
		if (!filesystem.IsWritable())
			return PSM_ERROR_ACCESS_DENIED;

		// Locate the file on disk, and delete it
		std::string PathOnDisk = this->LocateRealPath(normPath, false);
		std::filesystem::remove(std::filesystem::path(PathOnDisk));

		return PSM_ERROR_NO_ERROR;
	}

	std::shared_ptr<PsmFileHandle> Sandbox::OpenDirectory(std::string sandboxedPath) {
		std::string normPath = this->normalizePath(sandboxedPath);
		std::string pathOnDisk = this->LocateRealPath(normPath, false);
		FileSystem filesystem = this->findFilesystem(normPath, false);

		// Create a new PsmFileDescriptor 
		std::shared_ptr<PsmFileHandle> handle = PsmFileHandle::Create(normPath, pathOnDisk, static_cast<ScePssFileOpenFlag_t>(filesystem.IsWritable() ? SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_WRITE : SCE_PSS_FILE_OPEN_FLAG_READ));

		// Fail if its a file or it doesnt exist.
		if (this->IsFile(normPath) || !this->PathExist(normPath, false)) {
			handle->SetError(PSM_ERROR_PATH_NOT_FOUND);
			return handle;
		}

		if (!filesystem.IsRoot()) {
			handle->SetUnderyling(new DirectoryIterator(normPath, false));
		}
		else { // emulate the directory listing for the root "/" directory.
			std::vector<EmulatedDirectoryEntry> entries;

			for (FileSystem fs : this->filesystems) {
				// skip internal and root
				if (fs.IsSystem() || filesystem.IsRoot()) continue;
				
				EmulatedDirectoryEntry entry;
				entry.file = false;
				entry.size = 0;

				// only mark it as readonly if its not writable
				entry.readonly = !fs.IsWritable();

				// get the filename part of the path (i.e "Application" ..)
				entry.name = std::filesystem::path(fs.SandboxPath()).filename().string();
				entries.push_back(entry);
			}

			handle->SetUnderyling(new EmulatedDirectory(filesystem.SandboxPath(), entries));
		}
		
		return handle;
	}

	std::string Sandbox::LocateRealPath(std::string sandboxedPath, bool includeSystem) {
		std::string normPath = this->normalizePath(sandboxedPath);
		
		// find what filesystem the path is located in, (eg /Application) 
		FileSystem filesystem = this->findFilesystem(sandboxedPath, includeSystem);

		// Get the real path to this folder on disk
		std::filesystem::path fsRealPath = std::filesystem::path(filesystem.PathOnDisk());
		
		// Get the folder name inside the PSM Sandbox.
		std::string fsName = filesystem.SandboxPath();

		if (!this->IsFileSystemRootDirectory(normPath)) {
			// Subtract sandbox name from the full path, should result in a relative path from inside the specific sandboxed folder ..
			std::string pathRelativeToFilesystem = normPath.substr(fsName.length() + 1);

			// Append that file path to real path,
			fsRealPath.append(pathRelativeToFilesystem);
		}
		
		// Scan for same name w different casing
		// mirror exFAT-like behaviour on non-case sensitve filesystems.
		if (!std::filesystem::exists(fsRealPath)) { 
			std::string fsDirName = Path::UpDirectory(fsRealPath.string());
			std::string fsFname = fsRealPath.filename().string();

			if (std::filesystem::exists(fsDirName)) {

				std::error_code err;

				// scan the directory the file is supposed to be in;
				for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(fsDirName, err)) {
					std::string gotFname = entry.path().filename().string();

					// match anything that == same as first file but all uppercase;
					if (Format::ToUpper(gotFname) == Format::ToUpper(fsFname)) {
						fsRealPath = std::filesystem::path(Path::Combine(fsDirName, gotFname));
						Logger::Debug("ExFAT Fixer-Upper: " + fsRealPath.string());
					}
				}

				if (err) {
					Logger::Error(err.message());
				}
			}
		}

		// Swap slahses to the format used by the current Operating System,
		return Path::ChangeSlashesToNativeStyle(fsRealPath.string());
	}


}
