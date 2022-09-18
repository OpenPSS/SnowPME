#ifndef SNOW_PME_SANDBOX_H
#define SNOW_PME_SANDBOX_H 1
#include <IO/FileSystem.hpp>
#include <vector>
#include <fstream>
#include <mono/mono.h>

typedef struct PsmHandle {
	bool opened = false;
	bool rw = false;
	bool directory = false;
	bool encrypted = false;
	bool emulated = false;
	uint32_t failReason = 0;
	ScePssFileOpenFlag_t flags = (ScePssFileOpenFlag_t)0;
	std::string sandboxPath;
	std::string realPath;
	std::filesystem::directory_iterator* directoryFd = NULL;
	std::fstream* fileFd = NULL;
} PsmHandle;


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
		ScePssFileInformation_t Stat(std::string sandboxedPath, std::string setName);
		bool PathExist(std::string sandboxedPath);
		bool IsFile(std::string sandboxedPath);
		bool IsDirectory(std::string sandboxedPath);

		void CloseDirectory(PsmHandle* handle);
		void CloseFile(PsmHandle* handle);
		uint64_t GetSize(PsmHandle* handle);
		PsmHandle* OpenDirectory(std::string sandboxedPath);
		PsmHandle* OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags);
		std::string AbsolutePath(std::string sandboxedPath);
		std::string LocateRealPath(std::string sandboxedPath);
	};

}

#endif