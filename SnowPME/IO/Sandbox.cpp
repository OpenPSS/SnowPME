#include <IO/Sandbox.hpp>
#include <IO/Path.hpp>
#include <Util/StringUtils.hpp>
#include <filesystem>
#include <sys/stat.h>

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

		// Iterate over all files opened by the sandbox
		for (std::ifstream* file : this->openFiles) {
			file->close(); // close the file.
			delete file; // free up memory used by the handle
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
			psmPathInformation.uFlags |= PSM_IO_DIR;
		if ( ( (stats.st_mode & S_IREAD) != 0 && (stats.st_mode & S_IWRITE) == 0) || !filesystem->IsRewitable())
			psmPathInformation.uFlags |= PSM_IO_RO;

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

	std::string Sandbox::LocateRealPath(std::string sandboxedPath) {
		std::string absPath = this->AbsolutePath(sandboxedPath);
		
		// find what filesystem the path is located in, (eg /Application) 
		FileSystem* filesystem = this->findFilesystem(sandboxedPath);

		// Get the real path to this folder on disk
		std::filesystem::path fsRealPath = std::filesystem::path(filesystem->PathOnDisk());
		// Get the name inside the PSM Sandbox.
		std::string fsName = filesystem->SandboxPath();

		// Subtract sandbox name from the full path, should result in a relative path from inside the specific sandboxed folder ..
		std::string pathRelativeToFilesystem = absPath.substr(fsName.length()+1);

		// Append that file path to real path,
		fsRealPath.append(pathRelativeToFilesystem);

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