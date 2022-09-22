#ifndef SNOW_PME_SANDBOX_H
#define SNOW_PME_SANDBOX_H 1
#include <IO/DirectoryIterator.hpp>
#include <IO/FileSystem.hpp>
#include <vector>
#include <fstream>
#include <mono/mono.h>

namespace SnowPME::IO {
	typedef struct PsmHandle {
		bool opened = false;
		bool rw = false;
		bool directory = false;
		bool encrypted = false;
		bool emulated = false;
		uint32_t failReason = 0;
		ScePssFileOpenFlag_t flags = ScePssFileOpenFlag_t();
		std::ios_base::openmode iflags = std::ios_base::openmode();
		std::string sandboxPath;
		std::string realPath;
		size_t seekPos = 0;

		std::fstream* fileFd = NULL;
		DirectoryIterator* directoryFd = NULL;
	} PsmHandle;

	class Sandbox {	
	private:
		std::string currentWorkingDirectory;
		std::vector<FileSystem*> filesystems;
		FileSystem* findFilesystem(std::string sandboxedPath);
		bool isFileSystemRootDirectory(std::string sandboxedPath);
		void reopen(PsmHandle* handle);
	public:
		Sandbox(std::string gameFolder);
		~Sandbox();
		ScePssFileInformation_t Stat(std::string sandboxedPath, std::string setName);
		bool PathExist(std::string sandboxedPath);
		bool IsFile(std::string sandboxedPath);
		bool IsDirectory(std::string sandboxedPath);

		void CloseDirectory(PsmHandle* handle);
		void CloseFile(PsmHandle* handle);
		size_t GetSize(PsmHandle* handle);
		int ChangeSize(PsmHandle* handle, size_t newSize);
		int Seek(PsmHandle* handle, uint32_t offset, ScePssFileSeekType_t seekType);
		int DeleteFile(std::string sandboxedPath);
		size_t ReadFile(PsmHandle* handle, size_t numbBytes, char* buffer);
		size_t WriteFile(PsmHandle* handle, size_t numbBytes, char* buffer);
		std::string GetCurrentDirectory();
		int SetCurrentDirectory(std::string sandboxedPath);
		int CreateDirectory(std::string sandboxedPath);
		int DeleteDirectory(std::string sandboxedPath);
		int ReadDirectory(PsmHandle* handle, ScePssFileInformation_t* fileInfo);
		PsmHandle* OpenDirectory(std::string sandboxedPath);
		PsmHandle* OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags);		
		std::string AbsolutePath(std::string sandboxedPath);
		std::string LocateRealPath(std::string sandboxedPath);
	};

}

#endif