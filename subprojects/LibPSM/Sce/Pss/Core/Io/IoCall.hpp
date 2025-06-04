#ifndef LIB_PSS_IOCALL_H
#define LIB_PSS_IOCALL_H 1


#include <mono/mono.h>
#include <iostream>

namespace Sce::Pss::Core::Io {

	class IoCall
	{
	public:
		static int PsmClose(uint64_t handle);
		
		static int PsmDirectoryCreate(char* pszDirectoryPath);
		static int PsmDirectoryRemove(char* pszDirectoryPath);
		
		static int PsmDirectoryOpen(const char* pszDirectoryPath, const char* pszFileExtension, uint64_t* pDirectory);
		static int PsmDirectoryRead(uint64_t directory, ScePssFileInformation_t* pFileInfo);
		
		static int PsmDirectoryGetWorking(char* pszDirectoryPath, uint32_t uBufferSize);
		static int PsmDirectorySetWorking(char* pszDirectoryPath);

		static int PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile);
		static int PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile, bool includeSystem);
		static int PsmFileDelete(char* pszFileName);
		static int PsmFileGetInformation(uint64_t file, ScePssFileInformation_t* pFileInfo);
		static int PsmFileRead(uint64_t file, void* buffer, uint32_t uBytesToRead, uint32_t* puBytesRead);
		static int PsmFileWrite(uint64_t file, void* buffer, uint32_t uBytesToWrite, uint32_t* puBytesWritten);
		static int PsmFileSeek(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType);
		static int PsmFileFlush(uint64_t file);
		static int PsmFileGetSize(uint64_t file, uint32_t* puSize);
		static int PsmFileTruncate(uint64_t file, uint32_t uSize);

		static int PsmFileCopy(const char* pszOldName, const char* pszNewName, int32_t bMove);
		static int PsmFileSetAttributes(const char* pszFileName, uint32_t uFlags);
		static int PsmFileSetTimes(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime);
		static int PsmFileGetPathInformation(const char* pszFileName, ScePssFileInformation_t* pFileInfo);
	

	};
}

#endif