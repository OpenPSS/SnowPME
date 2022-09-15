#include <Io/Filesystem.hpp>
#include <LibPSM.hpp>

namespace SnowPME::IO {
	int Filesystem::PsmClose(uint64_t handle) {
		std::cout << "Filesystem::PsmClose Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmDirectoryCreate(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectoryCreate Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmDirectoryRemove(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectoryRemove Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmDirectoryOpen(const char* pszDirectoryPath, const char* pszFileExtension, uint64_t* pDirectory) {
		std::cout << "Filesystem::PsmDirectoryOpen Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmDirectoryRead(uint64_t directory, ScePssFileInformation_t* pFileInfo) {
		std::cout << "Filesystem::PsmDirectoryRead Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmDirectoryGetWorking(char* pszDirectoryPath, uint32_t uBufferSize) {
		std::cout << "Filesystem::PsmDirectoryGetWorking Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmDirectorySetWorking(char* pszDirectoryPath) {
		std::cout << "Filesystem::PsmDirectorySetWorking Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile) {
		std::cout << "Filesystem::PsmFileOpen Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileDelete(char* pszFileName) {
		std::cout << "Filesystem::PsmFileDelete Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileGetInformation(uint64_t file, ScePssFileInformation_t* pFileInfo) {
		std::cout << "Filesystem::PsmFileGetInformation Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileRead(uint64_t file, void* buffer, uint32_t uBytesToRead, uint32_t* puBytesRead) {
		std::cout << "Filesystem::PsmFileRead Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileWrite(uint64_t file, void* buffer, uint32_t uBytesToWrite, uint32_t* puBytesWritten) {
		std::cout << "Filesystem::PsmFileWrite Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileSeek(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType) {
		std::cout << "Filesystem::PsmFileSeek Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileFlush(uint64_t file) {
		std::cout << "Filesystem::PsmFileFlush Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileGetSize(uint64_t file, uint32_t* puSize) {
		std::cout << "Filesystem::PsmFileGetSize Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileTruncate(uint64_t file, uint32_t uSize) {
		std::cout << "Filesystem::PsmFileTruncate Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileCopy(const char* pszOldName, const char* pszNewName, int32_t bMove) {
		std::cout << "Filesystem::PsmFileCopy Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileSetAttributes(const char* pszFileName, uint32_t uFlags) {
		std::cout << "Filesystem::PsmFileSetAttributes Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileSetTimes(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime) {
		std::cout << "Filesystem::PsmFileSetTimes Not Implemented" << std::endl;
		return PSM_OK;
	}
	int Filesystem::PsmFileGetPathInformation(const char* pszFileName, ScePssFileInformation_t* pFileInfo) {
		std::cout << "Filesystem::PsmFileGetPathInformation Not Implemented" << std::endl;
		return PSM_OK;
	}
}
