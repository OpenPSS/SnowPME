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
	uint32_t failReason;
	ScePssFileOpenFlag_t flags;
	std::string sandboxPath;
	std::string realPath;
	std::filesystem::directory_iterator* directoryFd;
	std::fstream* fileFd;
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
		ScePssFileInformation_t StatFile(std::string sandboxedPath);
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