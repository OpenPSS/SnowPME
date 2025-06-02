#ifndef LIB_PSS_SANDBOX_H
#define LIB_PSS_SANDBOX_H 1
#include <Sce/Pss/Core/Io/DirectoryIterator.hpp>
#include <Sce/Pss/Core/Io/FileSystem.hpp>
#include <Sce/Pss/Core/Io/PsmFileHandle.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Io/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataList.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>

#include <vector>
#include <fstream>
#include <mono/mono.h>


namespace Sce::Pss::Core::Io {
	class Sandbox : public PsmUniqueObject<Sandbox> {
	private:
		std::string currentWorkingDirectory = "/";
		std::vector<FileSystem> filesystems;
		
		FileSystem findFilesystem(std::string sandboxedPath, bool includeSystem);
		void reopen(PsmFileHandle* handle);
		int readLicenseData();
		std::string normalizePath(std::string sandboxedPath);

	public:
		Sce::Pss::Core::Io::Edata::PsmDrm* GameDrmProvider = nullptr;
		Sandbox(std::string gameFolder);
		~Sandbox();

		ScePssFileInformation_t Stat(std::string sandboxedPath, std::string setName);
		bool IsFileSystemRootDirectory(std::string sandboxedPath);
		bool PathExist(std::string sandboxedPath, bool includeSystem);
		bool IsFile(std::string sandboxedPath);
		bool IsDirectory(std::string sandboxedPath);
		int ChangeSize(PsmFileHandle* handle, uint32_t newSize);
		int RemoveFile(std::string sandboxedPath);
		int CopyFile(std::string sandboxedSrcPath, std::string sandboxDestPath, bool move);
		std::string GetWorkingDirectory();
		int SetWorkingDirectory(std::string sandboxedPath);
		int MakeDirectory(std::string sandboxedPath);
		int RemoveDirectory(std::string sandboxedPath);
		int SetAttributes(std::string sandboxedPath, uint32_t attributes);
		int SetFileTimes(std::string sandboxedPath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime);
		PsmFileHandle* OpenDirectory(std::string sandboxedPath);
		PsmFileHandle* OpenFile(std::string sandboxedPath, ScePssFileOpenFlag_t flags, bool includeSystem);		
		std::string LocateRealPath(std::string sandboxedPath, bool includeSystem);
	};

}

#endif