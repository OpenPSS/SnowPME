#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>

#include <Debug/Logger.hpp>

#include <mono/mono.h>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Io::Edata;

namespace Sce::Pss::Core::Io {

	int IoCall::PsmClose(uint64_t handle) {
		LOG_FUNCTION();
		if (!Handles::IsValid(handle))
			return PSM_ERROR_INVALID_PARAMETER;
		
		PsmFileHandle* fd = Handles::Get<PsmFileHandle>(handle);
	
		if (fd != nullptr) return PSM_ERROR_INVALID_PARAMETER;
		if (!fd->IsOpen()) return PSM_ERROR_INVALID_PARAMETER;

		PsmFileHandle::Delete(fd);

		return PSM_ERROR_NO_ERROR;
	}

	int IoCall::PsmDirectoryCreate(char* pszDirectoryPath) {
		LOG_FUNCTION();
		if (pszDirectoryPath == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string sandboxPath = std::string(pszDirectoryPath);

		return Sandbox::UniqueObject()->MakeDirectory(sandboxPath);
	}

	int IoCall::PsmDirectoryRemove(char* pszDirectoryPath) {
		LOG_FUNCTION();
		if (pszDirectoryPath == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;


		std::string sandboxPath = std::string(pszDirectoryPath);

		return Sandbox::UniqueObject()->RemoveDirectory(sandboxPath);
	}

	int IoCall::PsmDirectoryOpen(const char* pszDirectoryPath, const char* pszFileExtension, uint64_t* pDirectory) {
		LOG_FUNCTION();
		if (pszDirectoryPath == nullptr || pDirectory == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;


		std::string sandboxPath = std::string(pszDirectoryPath);

		if (!Sandbox::UniqueObject()->PathExist(sandboxPath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		if (Sandbox::UniqueObject()->IsDirectory(sandboxPath)) {
			PsmFileHandle* directoryHandle = Sandbox::UniqueObject()->OpenDirectory(sandboxPath);
			RETURN_ERRORABLE_PSMOBJECT(directoryHandle, PsmFileHandle);
			
			*pDirectory = static_cast<uint64_t>(directoryHandle->Handle());
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_PATH_NOT_FOUND;
	}

	int IoCall::PsmDirectoryRead(uint64_t directory, ScePssFileInformation_t* pFileInfo) {
		LOG_FUNCTION();
		if (pFileInfo == nullptr || !Handles::IsValid(directory))
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(directory);

		if (!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER
			;
		if (handle->GetUnderlying() == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		int rd = handle->GetUnderlying()->Read(pFileInfo, sizeof(ScePssFileInformation_t));
		if (rd != sizeof(ScePssFileInformation_t)) return PSM_ERROR_PATH_NOT_FOUND;

		return PSM_ERROR_NO_ERROR;

	}

	int IoCall::PsmDirectoryGetWorking(char* pszDirectoryPath, uint32_t uBufferSize) {
		LOG_FUNCTION();
		if (pszDirectoryPath == nullptr || uBufferSize == 0)
			return PSM_ERROR_INVALID_PARAMETER;

		if (uBufferSize < PSM_PATH_MAX)
			return PSM_ERROR_BUFFER_FULL;

		memset(pszDirectoryPath, 0, uBufferSize);
		strncpy(pszDirectoryPath, Sandbox::UniqueObject()->GetWorkingDirectory().c_str(), uBufferSize - 1);

		return PSM_ERROR_NO_ERROR;
	}

	int IoCall::PsmDirectorySetWorking(char* pszDirectoryPath) {
		LOG_FUNCTION();
		if (pszDirectoryPath == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string sandboxPath = std::string(pszDirectoryPath);
		return Sandbox::UniqueObject()->SetWorkingDirectory(sandboxPath);
	}

	int IoCall::PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile) {
		LOG_FUNCTION();
		return IoCall::PsmFileOpen(pszFileName, uOpenFlags, phFile, false);
	}

	int IoCall::PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile, bool includeSystem) {
		if (pszFileName == nullptr || phFile == nullptr || strlen(pszFileName) > PSM_PATH_MAX) return PSM_ERROR_INVALID_PARAMETER;
		std::string sandboxedPath = std::string(pszFileName);

		if (!Sandbox::UniqueObject()->IsDirectory(sandboxedPath)) {
			PsmFileHandle* fileHandle = Sandbox::UniqueObject()->OpenFile(sandboxedPath, static_cast<ScePssFileOpenFlag_t>(uOpenFlags), includeSystem);
			RETURN_ERRORABLE_PSMOBJECT(fileHandle, PsmFileHandle);

			*phFile = static_cast<uint64_t>(fileHandle->Handle());
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_PATH_NOT_FOUND;
	}

	int IoCall::PsmFileDelete(char* pszFileName) {
		LOG_FUNCTION();
		if (pszFileName == nullptr) return PSM_ERROR_INVALID_PARAMETER;

		std::string sandboxPath = std::string(pszFileName);
		
		if (sandboxPath.length() > PSM_PATH_MAX)
			return PSM_ERROR_INVALID_PARAMETER;

		return Sandbox::UniqueObject()->RemoveFile(sandboxPath);

	}

	int IoCall::PsmFileGetInformation(uint64_t file, ScePssFileInformation_t* pFileInfo) { 
		LOG_FUNCTION();

		if (!Handles::IsValid(file) || pFileInfo == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;
		
		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(file);

		if (!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER;

		ScePssFileInformation_t fileInfo = Sandbox::UniqueObject()->Stat(handle->PathInSandbox(), handle->PathInSandbox());
		memcpy(pFileInfo, &fileInfo, sizeof(ScePssFileInformation_t));

		return PSM_ERROR_NO_ERROR;
	}

	int IoCall::PsmFileRead(uint64_t file, void* buffer, uint32_t uBytesToRead, uint32_t* puBytesRead) {
		LOG_FUNCTION();

		if (!Handles::IsValid(file) || buffer == nullptr || uBytesToRead == 0 || puBytesRead == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;


		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(file);

		if (!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER;

		*puBytesRead = handle->GetUnderlying()->Read(buffer, uBytesToRead);

		return PSM_ERROR_NO_ERROR;
	}

	int IoCall::PsmFileWrite(uint64_t file, void* buffer, uint32_t uBytesToWrite, uint32_t* puBytesWritten) {
		LOG_FUNCTION();

		if (!Handles::IsValid(file) || buffer == nullptr || uBytesToWrite == 0 || puBytesWritten == 0)
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(file);

		if (!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->IsEncrypted())
			return PSM_ERROR_ACCESS_DENIED;

		if (!handle->IsRewritable())
			return PSM_ERROR_ACCESS_DENIED;
		
		*puBytesWritten = reinterpret_cast<EdataStream*>(handle->GetUnderlying())->Write(buffer, uBytesToWrite);

		return PSM_ERROR_NO_ERROR;
	}

	int IoCall::PsmFileSeek(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType) {
		LOG_FUNCTION();
		if (!Handles::IsValid(file) || seekType > SCE_PSS_FILE_SEEK_TYPE_CURRENT)
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(file);
		
		if (handle == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		if(!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER;
		
		return reinterpret_cast<EdataStream*>(handle->GetUnderlying())->Seek(nOffset, seekType);
	}

	int IoCall::PsmFileFlush(uint64_t file) {
		LOG_FUNCTION();
		if (!Handles::IsValid(file))
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(file);
		
		if (handle == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->IsRewritable() || handle->IsEncrypted())
			return PSM_ERROR_ACCESS_DENIED;

		if (handle->GetUnderlying() == nullptr)
			return PSM_ERROR_INVALID_HANDLE;

		static_cast<EdataStream*>(handle->GetUnderlying())->Flush();
		return PSM_ERROR_NO_ERROR;
	}
	
	int IoCall::PsmFileGetSize(uint64_t file, uint32_t* puSize) {
		LOG_FUNCTION();
		if (puSize == nullptr || !Handles::IsValid(file))
			return PSM_ERROR_INVALID_PARAMETER;
		
		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(file);

		if (handle == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER;

		*puSize = static_cast<uint32_t>(reinterpret_cast<EdataStream*>(handle->GetUnderlying())->Length());

		return PSM_ERROR_NO_ERROR;
	}

	int IoCall::PsmFileTruncate(uint64_t file, uint32_t uSize) {
		LOG_FUNCTION();

		if (!Handles::IsValid(file))
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileHandle* handle = Handles::Get<PsmFileHandle>(file);

		if(!handle->IsOpen())
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->IsDirectory())
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->IsRewritable())
			return PSM_ERROR_ACCESS_DENIED;

		int errorcode = Sandbox::UniqueObject()->ChangeSize(handle, uSize);

		return errorcode;
	}
	int IoCall::PsmFileCopy(const char* pszOldName, const char* pszNewName, int32_t bMove) {
		LOG_FUNCTION();

		if (pszOldName == nullptr || pszNewName == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string srcSandboxPath = std::string(pszOldName);
		std::string dstSandboxPath = std::string(pszNewName);

		return Sandbox::UniqueObject()->CopyFile(srcSandboxPath, dstSandboxPath, static_cast<bool>(bMove));

	}
	int IoCall::PsmFileSetAttributes(const char* pszFileName, uint32_t uFlags) {
		LOG_FUNCTION();

		if (pszFileName == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string sandboxPath = std::string(pszFileName);

		return Sandbox::UniqueObject()->SetAttributes(sandboxPath, uFlags);
	}
	int IoCall::PsmFileSetTimes(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime) {
		LOG_FUNCTION();

		if (pszFileName == nullptr || pCreationTime == nullptr || pLastAccessTime == nullptr || pLastWriteTime == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string sandboxPath = std::string(pszFileName);

		time_t creationTime = FILETIME_TO_UNIX(*pCreationTime);
		time_t lastAccessTime = FILETIME_TO_UNIX(*pLastAccessTime);
		time_t lastWriteTime = FILETIME_TO_UNIX(*pLastWriteTime);

		return Sandbox::UniqueObject()->SetFileTimes(sandboxPath, creationTime, lastAccessTime, lastWriteTime);
	}

	int IoCall::PsmFileGetPathInformation(const char* pszFileName, ScePssFileInformation_t* pFileInfo) {
		LOG_FUNCTION();

		if (pFileInfo == nullptr || pszFileName == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		memset(pFileInfo, 0, sizeof(ScePssFileInformation_t));

		std::string sandboxPath = std::string(pszFileName);

		if (!Sandbox::UniqueObject()->PathExist(sandboxPath, false))
			return PSM_ERROR_NOT_FOUND;

		ScePssFileInformation_t fileinfo = Sandbox::UniqueObject()->Stat(sandboxPath, sandboxPath);
		memcpy(pFileInfo, &fileinfo, sizeof(ScePssFileInformation_t));

		return PSM_ERROR_NO_ERROR;
	}
}
