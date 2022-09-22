#include <IO/ICall.hpp>
#include <IO/Path.hpp>
#include <Runtime/AppGlobals.hpp>
#include <Debug/Logger.hpp>
#include <LibPSM.hpp>
#include <mono/mono.h>

using namespace SnowPME::Runtime;
using namespace SnowPME::Debug;

namespace SnowPME::IO {
	int ICall::PsmClose(uint64_t handle) {
		Logger::Debug(__func__);
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
		Logger::Debug(__func__);
		if (pszDirectoryPath == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		return psmSandbox->CreateDirectory(absolutePath);
	}
	int ICall::PsmDirectoryRemove(char* pszDirectoryPath) {
		Logger::Debug(__func__);
		if (pszDirectoryPath == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		return psmSandbox->DeleteDirectory(absolutePath);
	}
	int ICall::PsmDirectoryOpen(const char* pszDirectoryPath, const char* pszFileExtension, uint64_t* pDirectory) {
		Logger::Debug(__func__);
		if (pszDirectoryPath == NULL || pDirectory == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		if (pszFileExtension != NULL)
			Logger::Debug("Oh oh- pszFileExtension is not null.");

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);
		
		Logger::Debug("OPEN: " + relativePath);

		if (!psmSandbox->PathExist(absolutePath))
			return PSM_ERROR_PATH_NOT_FOUND;

		if (psmSandbox->IsDirectory(absolutePath)) {
			PsmHandle* directoryHandle = psmSandbox->OpenDirectory(absolutePath);
			
			if (directoryHandle->failReason != PSM_ERROR_NO_ERROR)
			{
				uint32_t failReason = directoryHandle->failReason;
				psmSandbox->CloseDirectory(directoryHandle);
				return failReason;
			}
			
			*pDirectory = (uint64_t)directoryHandle;
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_PATH_NOT_FOUND;
	}
	int ICall::PsmDirectoryRead(uint64_t directory, ScePssFileInformation_t* pFileInfo) {
		Logger::Debug(__func__);
		if (pFileInfo == NULL || directory == NULL)
			return PSM_ERROR_INVALID_PARAMETER;


		Sandbox* psmSandbox = AppGlobals::PsmSandbox();
		PsmHandle* handle = (PsmHandle*)directory;

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;


		return psmSandbox->ReadDirectory(handle, pFileInfo);

	}
	int ICall::PsmDirectoryGetWorking(char* pszDirectoryPath, uint32_t uBufferSize) {
		Logger::Debug(__func__);
		if (pszDirectoryPath == NULL || uBufferSize == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		if (uBufferSize < PSM_PATH_MAX)
			return PSM_ERROR_BUFFER_FULL;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();
		memset(pszDirectoryPath, 0, uBufferSize);
		strncpy(pszDirectoryPath, psmSandbox->GetCurrentDirectory().c_str(), uBufferSize - 1);

		return PSM_ERROR_NO_ERROR;
	}
	int ICall::PsmDirectorySetWorking(char* pszDirectoryPath) {
		Logger::Debug(__func__);
		if (pszDirectoryPath == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();
		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);
		return psmSandbox->SetCurrentDirectory(absolutePath);
	}

	int ICall::PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile) {
		Logger::Debug(__func__);
		if (pszFileName == NULL || phFile == NULL || strlen(pszFileName) > PSM_PATH_MAX)
			return PSM_ERROR_INVALID_PARAMETER;


		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		if (!psmSandbox->IsDirectory(absolutePath)) {
			PsmHandle* fileHandle = psmSandbox->OpenFile(absolutePath, (ScePssFileOpenFlag_t)uOpenFlags);

			if (fileHandle->failReason != PSM_ERROR_NO_ERROR)
			{
				uint32_t failReason = fileHandle->failReason;
				psmSandbox->CloseFile(fileHandle);
				return failReason;
			}

			*phFile = (uint64_t)fileHandle;
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_PATH_NOT_FOUND;
	}
	int ICall::PsmFileDelete(char* pszFileName) {
		Logger::Debug(__func__);
		if (pszFileName == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszFileName);
		
		if (relativePath.length() > PSM_PATH_MAX)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		return psmSandbox->DeleteFile(absolutePath);

	}
	int ICall::PsmFileGetInformation(uint64_t file, ScePssFileInformation_t* pFileInfo) {
		Logger::Error("PsmFileGetInformation Not Implemented");
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileRead(uint64_t file, void* buffer, uint32_t uBytesToRead, uint32_t* puBytesRead) {
		Logger::Debug(__func__);

		if (file == NULL || buffer == NULL || uBytesToRead == NULL || puBytesRead == NULL)
			return PSM_ERROR_INVALID_PARAMETER;


		PsmHandle* handle = (PsmHandle*)file;

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;


		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		*puBytesRead = psmSandbox->ReadFile(handle, uBytesToRead, (char*)buffer);

		return PSM_ERROR_NO_ERROR;
	}

	int ICall::PsmFileWrite(uint64_t file, void* buffer, uint32_t uBytesToWrite, uint32_t* puBytesWritten) {
		Logger::Debug(__func__);
		if (file == NULL || buffer == NULL || uBytesToWrite == NULL || puBytesWritten == NULL)
			return PSM_ERROR_INVALID_PARAMETER;


		PsmHandle* handle = (PsmHandle*)file;

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->rw)
			return PSM_ERROR_ACCESS_DENIED;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		*puBytesWritten = psmSandbox->WriteFile(handle, uBytesToWrite, (char*)buffer);

		return PSM_ERROR_NO_ERROR;
	}
	int ICall::PsmFileSeek(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType) {
		Logger::Debug(__func__);
		if (file == NULL || seekType > SCE_PSS_FILE_SEEK_TYPE_CURRENT)
			return PSM_ERROR_INVALID_PARAMETER;

		PsmHandle* handle = (PsmHandle*)file;

		if(!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();
		return psmSandbox->Seek(handle, nOffset, seekType);
	}
	int ICall::PsmFileFlush(uint64_t file) {
		Logger::Error("PsmFileFlush Not Implemented");
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileGetSize(uint64_t file, uint32_t* puSize) {
		Logger::Debug(__func__);
		if (puSize == NULL || file == NULL)
			return PSM_ERROR_INVALID_PARAMETER;
		
		PsmHandle* handle = (PsmHandle*)file;

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();
		*puSize = psmSandbox->GetSize(handle);

		return PSM_ERROR_NO_ERROR;
	}
	int ICall::PsmFileTruncate(uint64_t file, uint32_t uSize) {
		Logger::Debug(__func__);
		if (file == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		PsmHandle* handle = (PsmHandle*)file;

		if(!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->rw)
			return PSM_ERROR_ACCESS_DENIED;

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();
		int errorcode = psmSandbox->ChangeSize(handle, uSize);

		return errorcode;
	}
	int ICall::PsmFileCopy(const char* pszOldName, const char* pszNewName, int32_t bMove) {
		Logger::Error("PsmFileCopy Not Implemented");
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileSetAttributes(const char* pszFileName, uint32_t uFlags) {
		Logger::Error("PsmFileSetAttributes Not Implemented");
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileSetTimes(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime) {
		Logger::Error("PsmFileSetTimes Not Implemented");
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int ICall::PsmFileGetPathInformation(const char* pszFileName, ScePssFileInformation_t* pFileInfo) {
		Logger::Debug(__func__);

		if (pFileInfo == NULL || pszFileName == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		memset(pFileInfo, 0, sizeof(ScePssFileInformation_t));

		Sandbox* psmSandbox = AppGlobals::PsmSandbox();

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = psmSandbox->AbsolutePath(relativePath);

		Logger::Debug("PathInfo: " + relativePath);

		if (!psmSandbox->PathExist(absolutePath))
			return PSM_ERROR_NOT_FOUND;

		ScePssFileInformation_t fileinfo = psmSandbox->Stat(absolutePath, relativePath);
		memcpy(pFileInfo, &fileinfo, sizeof(ScePssFileInformation_t));

		return PSM_ERROR_NO_ERROR;
	}
}
