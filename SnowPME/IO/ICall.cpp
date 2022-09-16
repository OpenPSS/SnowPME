#include <IO/ICall.hpp>
#include <IO/Path.hpp>
#include <Runtime/AppGlobals.hpp>

#include <LibPSM.hpp>

using namespace SnowPME::Runtime;

namespace SnowPME::IO {
	int ICall::PsmClose(uint64_t handle) {
		std::cout << "Filesystem::PsmClose Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmDirectoryCreate(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectoryCreate Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmDirectoryRemove(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectoryRemove Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmDirectoryOpen(const char* pszDirectoryPath, const char* pszFileExtension, uint64_t* pDirectory) {
		std::cout << "Filesystem::PsmDirectoryOpen Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmDirectoryRead(uint64_t directory, ScePssFileInformation_t* pFileInfo) {
		std::cout << "Filesystem::PsmDirectoryRead Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmDirectoryGetWorking(char* pszDirectoryPath, uint32_t uBufferSize) {
		std::cout << "Filesystem::PsmDirectoryGetWorking Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmDirectorySetWorking(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectorySetWorking Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile) {
		std::cout << "Filesystem::PsmFileOpen Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileDelete(char* pszFileName) {
		std::cout << "Filesystem::PsmFileDelete Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileGetInformation(uint64_t file, ScePssFileInformation_t* pFileInfo) {
		std::cout << "Filesystem::PsmFileGetInformation Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileRead(uint64_t file, void* buffer, uint32_t uBytesToRead, uint32_t* puBytesRead) {
		std::cout << "Filesystem::PsmFileRead Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileWrite(uint64_t file, void* buffer, uint32_t uBytesToWrite, uint32_t* puBytesWritten) {
		std::cout << "Filesystem::PsmFileWrite Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileSeek(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType) {
		std::cout << "Filesystem::PsmFileSeek Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileFlush(uint64_t file) {
		std::cout << "Filesystem::PsmFileFlush Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileGetSize(uint64_t file, uint32_t* puSize) {
		std::cout << "Filesystem::PsmFileGetSize Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileTruncate(uint64_t file, uint32_t uSize) {
		std::cout << "Filesystem::PsmFileTruncate Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileCopy(const char* pszOldName, const char* pszNewName, int32_t bMove) {
		std::cout << "Filesystem::PsmFileCopy Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileSetAttributes(const char* pszFileName, uint32_t uFlags) {
		std::cout << "Filesystem::PsmFileSetAttributes Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileSetTimes(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime) {
		std::cout << "Filesystem::PsmFileSetTimes Not Implemented" << std::endl;
		return PSM_OK;
	}
	int ICall::PsmFileGetPathInformation(const char* pszFileName, ScePssFileInformation_t* pFileInfo) {
		if (pFileInfo == NULL)
			return PSM_ERROR_IO_ESRCH;
		memset(pFileInfo, 0, sizeof(ScePssFileInformation_t));

		if (!pFileInfo)
			return PSM_ERROR_IO_ESRCH;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		if (psmSandbox->IsDirectory(absolutePath))
			return PSM_ERROR_IO_EISDIR;

		if (!psmSandbox->PathExist(absolutePath))
			return PSM_ERROR_IO_EPERM;


		ScePssFileInformation_t fileinfo = psmSandbox->StatFile(relativePath);
		memcpy(pFileInfo, &fileinfo, sizeof(ScePssFileInformation_t));

		return PSM_OK;
	}
}
