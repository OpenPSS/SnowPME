#include <IO/ICall.hpp>
#include <IO/Path.hpp>
#include <Runtime/AppGlobals.hpp>

#include <LibPSM.hpp>

using namespace SnowPME::Runtime;

namespace SnowPME::IO {
	int ICall::PsmClose(uint64_t handle) {
		if (handle == NULL)
			return PSM_ERROR_INVALID_PARAMETER;
		
		Sandbox* psmSandbox = AppGlobals::PsmSandbox();
		PsmHandle* psmHandle = (PsmHandle*)handle;
	
		if (!psmHandle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (psmHandle->directory) {
			psmSandbox->CloseDirectory(psmHandle);
		}
		else {
			psmSandbox->CloseFile(psmHandle);
		}
			
		return PSM_ERROR_NO_ERROR;
	}
	int ICall::PsmDirectoryCreate(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectoryCreate Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmDirectoryRemove(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectoryRemove Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmDirectoryOpen(const char* pszDirectoryPath, const char* pszFileExtension, uint64_t* pDirectory) {
		if (pszDirectoryPath == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		if (pDirectory == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		if (!psmSandbox->PathExist(absolutePath))
			return PSM_ERROR_PATH_NOT_FOUND;

		if (psmSandbox->IsDirectory(absolutePath)) {
			PsmHandle* directoryHandle = psmSandbox->OpenDirectory(absolutePath);
			*pDirectory = (uint64_t)directoryHandle;
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_PATH_NOT_FOUND;
	}
	int ICall::PsmDirectoryRead(uint64_t directory, ScePssFileInformation_t* pFileInfo) {
		std::cout << "Filesystem::PsmDirectoryRead Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmDirectoryGetWorking(char* pszDirectoryPath, uint32_t uBufferSize) {
		std::cout << "Filesystem::PsmDirectoryGetWorking Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmDirectorySetWorking(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectorySetWorking Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile) {
		std::cout << "Filesystem::PsmFileOpen Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileDelete(char* pszFileName) {
		std::cout << "Filesystem::PsmFileDelete Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileGetInformation(uint64_t file, ScePssFileInformation_t* pFileInfo) {
		std::cout << "Filesystem::PsmFileGetInformation Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileRead(uint64_t file, void* buffer, uint32_t uBytesToRead, uint32_t* puBytesRead) {
		std::cout << "Filesystem::PsmFileRead Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileWrite(uint64_t file, void* buffer, uint32_t uBytesToWrite, uint32_t* puBytesWritten) {
		std::cout << "Filesystem::PsmFileWrite Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileSeek(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType) {
		std::cout << "Filesystem::PsmFileSeek Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileFlush(uint64_t file) {
		std::cout << "Filesystem::PsmFileFlush Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileGetSize(uint64_t file, uint32_t* puSize) {
		std::cout << "Filesystem::PsmFileGetSize Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileTruncate(uint64_t file, uint32_t uSize) {
		std::cout << "Filesystem::PsmFileTruncate Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileCopy(const char* pszOldName, const char* pszNewName, int32_t bMove) {
		std::cout << "Filesystem::PsmFileCopy Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileSetAttributes(const char* pszFileName, uint32_t uFlags) {
		std::cout << "Filesystem::PsmFileSetAttributes Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileSetTimes(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime) {
		std::cout << "Filesystem::PsmFileSetTimes Not Implemented" << std::endl;
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileGetPathInformation(const char* pszFileName, ScePssFileInformation_t* pFileInfo) {
		// Check arguments
		if (pFileInfo == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		if (pFileInfo == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		// Implement function
		memset(pFileInfo, 0, sizeof(ScePssFileInformation_t));

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		if (psmSandbox->IsDirectory(absolutePath))
			return PSM_ERROR_NOT_FOUND;

		if (!psmSandbox->PathExist(absolutePath))
			return PSM_ERROR_NOT_FOUND;


		ScePssFileInformation_t fileinfo = psmSandbox->StatFile(relativePath);
		memcpy(pFileInfo, &fileinfo, sizeof(ScePssFileInformation_t));

		return PSM_ERROR_NO_ERROR;
	}
}
