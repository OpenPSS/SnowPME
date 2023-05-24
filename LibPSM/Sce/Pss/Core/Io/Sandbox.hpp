#ifndef LIB_PSS_SANDBOX_H
#define LIB_PSS_SANDBOX_H 1
#include <Sce/Pss/Core/Io/DirectoryIterator.hpp>
#include <Sce/Pss/Core/Io/FileSystem.hpp>
#include <vector>
#include <fstream>
#include <mono/mono.h>


namespace Sce::Pss::Core::Io {
	typedef struct PsmFileDescriptor {
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
	} PsmFileDescriptor;

	class Sandbox {	
	private:
		std::string currentWorkingDirectory;
		std::vector<FileSystem*> filesystems;
		FileSystem* findFilesystem(std::string sandboxedPath);
		void reopen(PsmFileDescriptor* handle);
	public:
		Sandbox(std::string gameFolder);
		~Sandbox();
		ScePssFileInformation_t Stat(std::string sandboxedPath, std::string setName);
		bool IsFileSystemRootDirectory(std::string sandboxedPath);
		bool PathExist(std::string sandboxedPath);
		bool IsFile(std::string sandboxedPath);
		bool IsDirectory(std::string sandboxedPath);
		void CloseDirectory(PsmFileDescriptor* handle);
		void CloseFile(PsmFileDescriptor* handle);
		size_t GetSize(PsmFileDescriptor* handle);
		int ChangeSize(PsmFileDescriptor* handle, size_t newSize);
		int Seek(PsmFileDescriptor* handle, uint32_t offset, ScePssFileSeekType_t seekType);
		int DeleteFile(std::string sandboxedPath);
		size_t ReadFile(PsmFileDescriptor* handle, size_t numbBytes, char* buffer);
		size_t WriteFile(PsmFileDescriptor* handle, size_t numbBytes, char* buffer);
		int FlushFile(PsmFileDescriptor* handle);
		int CopyFile(std::string sandboxedSrcPath, std::string sandboxDestPath, bool move);
		std::string GetCurrentDirectory();
		int SetCurrentDirectory(std::string sandboxedPath);
		int CreateDirectory(std::string sandboxedPath);
		int DeleteDirectory(std::string sandboxedPath);
		int ReadDirectory(PsmFileDescriptor* handle, ScePssFileInformation_t* fileInfo);
		int SetAttributes(std::string sandboxedPath, uint32_t attributes);
		int SetFileTimes(std::string sandboxedPath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime);
		PsmFileDescriptor* OpenDirectory(std::string sandboxedPath);
		PsmFileDescriptor* OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags);		
		std::string AbsolutePath(std::string sandboxedPath);
		std::string LocateRealPath(std::string sandboxedPath);
	};

}

#endif