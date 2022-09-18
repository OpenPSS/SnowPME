#ifndef SNOW_PME_SANDBOX_H
#define SNOW_PME_SANDBOX_H 1

#include <IO/FileSystem.hpp>
#include <vector>
#include <fstream>
#include <mono/mono.h>

typedef struct PsmHandle {
	bool opened;
	bool rw;
	bool directory;
	bool encrypted;
	bool emulated;
	std::string sandboxPath;
	std::string realPath;
	std::filesystem::directory_iterator* directoryFd;
	std::ifstream* fileFd;
} PsmHandle;

typedef enum PsmFileMode : uint32_t {
	PSM_IO_DIR = 0x2,
	PSM_IO_RO = 0x1,
} PsmFileMode;

namespace SnowPME::IO {
	class Sandbox {	
	private:
		std::string currentWorkingDirectory;
		std::vector<FileSystem*> filesystems;
		FileSystem* findFilesystem(std::string sandboxedPath);
		bool isFileSystemRootDirectory(std::string sandboxedPath);
	public:
		Sandbox(std::string gameFolder);
		~Sandbox();
		ScePssFileInformation_t StatFile(std::string sandboxedPath);
		bool PathExist(std::string sandboxedPath);
		bool IsFile(std::string sandboxedPath);
		bool IsDirectory(std::string sandboxedPath);

		void CloseDirectory(PsmHandle* handle);
		void CloseFile(PsmHandle* handle);

		PsmHandle* OpenDirectory(std::string sandboxedPath);

		std::string AbsolutePath(std::string sandboxedPath);
		std::string LocateRealPath(std::string sandboxedPath);
	};

}

#endif