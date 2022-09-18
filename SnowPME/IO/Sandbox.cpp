#include <IO/Sandbox.hpp>
#include <IO/Path.hpp>
#include <Util/StringUtils.hpp>
#include <filesystem>
#include <sys/stat.h>
#include <mono/mono.h>
#include <LibPSM.hpp>

using namespace SnowPME::Util;

namespace SnowPME::IO {


	Sandbox::Sandbox(std::string gameFolder) {
		std::filesystem::path gamePath = std::filesystem::path(gameFolder);
		std::filesystem::path applicationPath = std::filesystem::path(gameFolder).append("Application");
		std::filesystem::path documentsPath = std::filesystem::path(gameFolder).append("Documents");
		std::filesystem::path tempPath = std::filesystem::path(gameFolder).append("Temp");

		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(applicationPath).string(), "/Application", false));
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(documentsPath).string(), "/Documents", true));
		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(tempPath).string(), "/Temp", true));

		this->filesystems.push_back(new FileSystem(std::filesystem::absolute(gamePath).string(), "/", false));

		this->currentWorkingDirectory = "/";

	}
	Sandbox::~Sandbox() {
		// Iterate over all fileystems
		for (FileSystem* filesystem : this->filesystems) {
			delete filesystem; // delete the filesystem
		}

		Sandbox::filesystems.clear(); // Clear the filesystems vector
	}

	FileSystem* Sandbox::findFilesystem(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		for (FileSystem* filesystem : Sandbox::filesystems) {
			if (StringUtils::ToLower(absPath).starts_with(StringUtils::ToLower(filesystem->SandboxPath()))) {
				return filesystem;
			}
		}

		throw std::exception("FileSystem not found ?? ??");
	}

	ScePssFileInformation_t Sandbox::StatFile(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);

		FileSystem* filesystem = this->findFilesystem(sandboxedPath);

		struct stat stats;
		stat(this->LocateRealPath(absPath).c_str(), &stats);

		ScePssFileInformation_t psmPathInformation;
		memset(&psmPathInformation, 0, sizeof(ScePssFileInformation_t));

		strncpy(psmPathInformation.szName, sandboxedPath.c_str(), PSM_PATH_MAX);
		psmPathInformation.uFileSize = stats.st_size;
		psmPathInformation.tCreationTime = stats.st_ctime;
		psmPathInformation.tLastWriteTime = stats.st_mtime;
		psmPathInformation.tLastAccessTime = stats.st_atime;

		if ((stats.st_mode & S_IFDIR) != 0)
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_DIRECTORY;

		if (((stats.st_mode & S_IREAD) != 0 && (stats.st_mode & S_IWRITE) == 0) || !filesystem->IsRewitable())
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_READONLY;

		if (filesystem->IsEncrypted())
			psmPathInformation.uFlags |= SCE_PSS_FILE_FLAG_ENCRYPTED;


		return psmPathInformation;
	}

	bool Sandbox::isFileSystemRootDirectory(std::string sandboxedPath) {
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

		if (this->isFileSystemRootDirectory(absPath))
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

		if (this->isFileSystemRootDirectory(absPath))
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
			if (handle->opened && handle->fileFd != NULL) {
				delete handle->directoryFd;
			}
			handle->opened = false;
			delete handle;
		}
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

	uint64_t Sandbox::GetSize(PsmHandle* handle) {
		if (!handle->encrypted) {
			return std::filesystem::file_size(handle->realPath);
		}
		return 0;
	}

	PsmHandle* Sandbox::OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		std::string realPath = this->LocateRealPath(absPath);

		FileSystem* filesystem = this->findFilesystem(absPath);

		PsmHandle* handle = new PsmHandle();
		memset(handle, 0, sizeof(PsmHandle));

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

		if (!openRw && !this->PathExist(absPath)) {
			handle->opened = false;
			handle->failReason = PSM_ERROR_PATH_NOT_FOUND;
			return handle;
		}


		// Calculate mode

		std::fstream::ios_base::openmode openmode = 0;
		openmode |= std::ios::_Nocreate;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_READ) != 0)
			openmode |= std::ios::in;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_WRITE) != 0)
			openmode |= std::ios::out;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_BINARY) != 0)
			openmode |= std::ios::binary;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_TEXT) != 0)
			openmode |= std::ios::trunc;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE) != 0)
			openmode ^= std::ios::trunc;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_APPEND) != 0)
			openmode |= std::ios::ate;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_NOREPLACE) != 0)
			openmode |= std::ios::_Noreplace;

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE) != 0)
			openmode ^= std::ios::_Nocreate;
			


		std::fstream* str = new std::fstream();
		str->open(realPath, openmode);

		handle->failReason = PSM_ERROR_NO_ERROR;
		handle->opened = true;
		handle->fileFd = str;

		return handle;
	}

	PsmHandle* Sandbox::OpenDirectory(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		std::string realPath = this->LocateRealPath(absPath);

		FileSystem* filesystem = this->findFilesystem(absPath);

		std::filesystem::directory_iterator* iterator = new std::filesystem::directory_iterator(realPath);

		PsmHandle* handle = new PsmHandle();
		memset(handle, 0, sizeof(PsmHandle));

		handle->opened = true;
		handle->rw = filesystem->IsRewitable();
		handle->encrypted = filesystem->IsEncrypted();
		handle->emulated = filesystem->IsEmulated();
		handle->directory = true;

		handle->flags = SCE_PSS_FILE_OPEN_FLAG_READ;
		handle->sandboxPath = absPath;
		handle->realPath = realPath;
		handle->directoryFd = iterator;
		handle->fileFd = NULL;
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

		if (!this->isFileSystemRootDirectory(absPath)) {
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