#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>

#include <Debug/Logger.hpp>
#include <LibPSM.hpp>
#include <mono/mono.h>

#include <LibShared.hpp>


namespace Sce::Pss::Core::Io {
	using namespace Shared::Debug;
	using namespace Sce::Pss::Core::System;

	int ICall::PsmClose(uint64_t handle) {
		Logger::Debug(__FUNCTION__);
		if (!Handles::IsValid(handle))
			return PSM_ERROR_INVALID_PARAMETER;
		
		PsmFileDescriptor* fd = Handles::Get<PsmFileDescriptor>(handle);
	
		if (!fd->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (fd->directory) {
			Sandbox::ApplicationSandbox->CloseDirectory(fd);
		}
		else {
			Sandbox::ApplicationSandbox->CloseFile(fd);
		}

		Handles::Delete(handle);
		return PSM_ERROR_NO_ERROR;
	}

	int ICall::PsmDirectoryCreate(char* pszDirectoryPath) {
		Logger::Debug(__FUNCTION__);
		if (pszDirectoryPath == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);

		return Sandbox::ApplicationSandbox->CreateDirectory(absolutePath);
	}

	int ICall::PsmDirectoryRemove(char* pszDirectoryPath) {
		Logger::Debug(__FUNCTION__);
		if (pszDirectoryPath == NULL)
			return PSM_ERROR_INVALID_PARAMETER;


		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);

		Logger::Debug("DeleteDirectory: " + absolutePath);

		return Sandbox::ApplicationSandbox->DeleteDirectory(absolutePath);
	}

	int ICall::PsmDirectoryOpen(const char* pszDirectoryPath, const char* pszFileExtension, uint64_t* pDirectory) {
		Logger::Debug(__FUNCTION__);
		if (pszDirectoryPath == NULL || pDirectory == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		if (pszFileExtension != NULL)
			Logger::Debug("Oh oh- pszFileExtension is not null.");

		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);
		
		Logger::Debug("DirectoryOpen: " + relativePath);

		if (!Sandbox::ApplicationSandbox->PathExist(absolutePath, false))
			return PSM_ERROR_PATH_NOT_FOUND;

		if (Sandbox::ApplicationSandbox->IsDirectory(absolutePath)) {
			PsmFileDescriptor* directoryHandle = Sandbox::ApplicationSandbox->OpenDirectory(absolutePath);
			
			if (directoryHandle->failReason != PSM_ERROR_NO_ERROR)
			{
				uint32_t failReason = directoryHandle->failReason;
				Sandbox::ApplicationSandbox->CloseDirectory(directoryHandle);
				return failReason;
			}
			
			
			*pDirectory = Handles::Create(directoryHandle);
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_PATH_NOT_FOUND;
	}

	int ICall::PsmDirectoryRead(uint64_t directory, ScePssFileInformation_t* pFileInfo) {
		Logger::Debug(__FUNCTION__);
		if (pFileInfo == NULL || !Handles::IsValid(directory))
			return PSM_ERROR_INVALID_PARAMETER;


		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(directory);

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;


		return Sandbox::ApplicationSandbox->ReadDirectory(handle, pFileInfo);

	}

	int ICall::PsmDirectoryGetWorking(char* pszDirectoryPath, uint32_t uBufferSize) {
		Logger::Debug(__FUNCTION__);
		if (pszDirectoryPath == NULL || uBufferSize == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		if (uBufferSize < PSM_PATH_MAX)
			return PSM_ERROR_BUFFER_FULL;

		memset(pszDirectoryPath, 0, uBufferSize);
		strncpy(pszDirectoryPath, Sandbox::ApplicationSandbox->GetCurrentDirectory().c_str(), uBufferSize - 1);

		return PSM_ERROR_NO_ERROR;
	}

	int ICall::PsmDirectorySetWorking(char* pszDirectoryPath) {
		Logger::Debug(__FUNCTION__);
		if (pszDirectoryPath == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string relativePath = std::string(pszDirectoryPath);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);
		return Sandbox::ApplicationSandbox->SetCurrentDirectory(absolutePath);
	}

	int ICall::PsmFileOpen(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile) {
		Logger::Debug(__FUNCTION__);
		return ICall::PsmFileOpenSystem(pszFileName, uOpenFlags, phFile, false);
	}

	int ICall::PsmFileOpenSystem(char* pszFileName, uint32_t uOpenFlags, uint64_t* phFile, bool includeSystem) {
		if (pszFileName == nullptr || phFile == nullptr || strlen(pszFileName) > PSM_PATH_MAX)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);
		Logger::Debug("Accessing: "+relativePath);

		if (!Sandbox::ApplicationSandbox->IsDirectory(absolutePath)) {
			PsmFileDescriptor* fileHandle = Sandbox::ApplicationSandbox->OpenFile(absolutePath, (ScePssFileOpenFlag_t)uOpenFlags, includeSystem);

			if (fileHandle->failReason != PSM_ERROR_NO_ERROR)
			{
				uint32_t failReason = fileHandle->failReason;
				Sandbox::ApplicationSandbox->CloseFile(fileHandle);
				return failReason;
			}

			*phFile = (uint64_t)Handles::Create(fileHandle);
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_PATH_NOT_FOUND;
	}

	int ICall::PsmFileDelete(char* pszFileName) {
		Logger::Debug(__FUNCTION__);
		if (pszFileName == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string relativePath = std::string(pszFileName);
		
		if (relativePath.length() > PSM_PATH_MAX)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);

		Logger::Debug("DeleteFile: " + absolutePath);

		return Sandbox::ApplicationSandbox->DeleteFile(absolutePath);

	}

	int ICall::PsmFileGetInformation(uint64_t file, ScePssFileInformation_t* pFileInfo) { 
		Logger::Debug(__FUNCTION__);

		if (!Handles::IsValid(file) || pFileInfo == NULL)
			return PSM_ERROR_INVALID_PARAMETER;
		
		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(file);

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		ScePssFileInformation_t fileInfo = Sandbox::ApplicationSandbox->Stat(handle->sandboxPath, handle->sandboxPath);
		memcpy(pFileInfo, &fileInfo, sizeof(ScePssFileInformation_t));

		return PSM_ERROR_NO_ERROR;
	}

	int ICall::PsmFileRead(uint64_t file, void* buffer, uint32_t uBytesToRead, uint32_t* puBytesRead) {
		Logger::Debug(__FUNCTION__);

		if (!Handles::IsValid(file) || buffer == NULL || uBytesToRead == NULL || puBytesRead == NULL)
			return PSM_ERROR_INVALID_PARAMETER;


		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(file);

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;


		
		*puBytesRead = Sandbox::ApplicationSandbox->ReadFile(handle, uBytesToRead, (char*)buffer);

		return PSM_ERROR_NO_ERROR;
	}

	int ICall::PsmFileWrite(uint64_t file, void* buffer, uint32_t uBytesToWrite, uint32_t* puBytesWritten) {
		Logger::Debug(__FUNCTION__);
		if (!Handles::IsValid(file) || buffer == nullptr || uBytesToWrite == NULL || puBytesWritten == nullptr)
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(file);

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->rw)
			return PSM_ERROR_ACCESS_DENIED;

		
		*puBytesWritten = Sandbox::ApplicationSandbox->WriteFile(handle, uBytesToWrite, (char*)buffer);

		return PSM_ERROR_NO_ERROR;
	}

	int ICall::PsmFileSeek(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType) {
		Logger::Debug(__FUNCTION__);
		if (!Handles::IsValid(file) || seekType > SCE_PSS_FILE_SEEK_TYPE_CURRENT)
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(file);

		if(!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		return Sandbox::ApplicationSandbox->Seek(handle, nOffset, seekType);
	}

	int ICall::PsmFileFlush(uint64_t file) {
		Logger::Debug(__FUNCTION__);
		if (!Handles::IsValid(file))
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(file);
		return Sandbox::ApplicationSandbox->FlushFile(handle);
	}
	
	int ICall::PsmFileGetSize(uint64_t file, uint32_t* puSize) {
		Logger::Debug(__FUNCTION__);
		if (puSize == NULL || !Handles::IsValid(file))
			return PSM_ERROR_INVALID_PARAMETER;
		
		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(file);

		if (!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		*puSize = Sandbox::ApplicationSandbox->GetSize(handle);

		return PSM_ERROR_NO_ERROR;
	}

	int ICall::PsmFileTruncate(uint64_t file, uint32_t uSize) {
		Logger::Debug(__FUNCTION__);
		if (!Handles::IsValid(file))
			return PSM_ERROR_INVALID_PARAMETER;

		PsmFileDescriptor* handle = Handles::Get<PsmFileDescriptor>(file);

		if(!handle->opened)
			return PSM_ERROR_INVALID_PARAMETER;

		if (handle->directory)
			return PSM_ERROR_INVALID_PARAMETER;

		if (!handle->rw)
			return PSM_ERROR_ACCESS_DENIED;

		int errorcode = Sandbox::ApplicationSandbox->ChangeSize(handle, uSize);

		return errorcode;
	}
	int ICall::PsmFileCopy(const char* pszOldName, const char* pszNewName, int32_t bMove) {
		Logger::Debug(__FUNCTION__);
		if (pszOldName == NULL || pszNewName == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string srcRelativePath = std::string(pszOldName);
		std::string srcAbsolutePath = Sandbox::ApplicationSandbox->AbsolutePath(srcRelativePath);

		std::string dstRelativePath = std::string(pszNewName);
		std::string dstAbsolutePath = Sandbox::ApplicationSandbox->AbsolutePath(dstRelativePath);

		return Sandbox::ApplicationSandbox->CopyFile(srcAbsolutePath, dstAbsolutePath, (bool)bMove);

	}
	int ICall::PsmFileSetAttributes(const char* pszFileName, uint32_t uFlags) {
		Logger::Debug(__FUNCTION__);
		if (pszFileName == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);

		if (!Sandbox::ApplicationSandbox->PathExist(absolutePath, false))
			return PSM_ERROR_NOT_FOUND;

		return Sandbox::ApplicationSandbox->SetAttributes(absolutePath, uFlags);
	}
	int ICall::PsmFileSetTimes(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime) {
		Logger::Debug(__FUNCTION__);
		if (pszFileName == NULL || pCreationTime == NULL || pLastAccessTime == NULL || pLastWriteTime == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);

		time_t creationTime = FILETIME_TO_UNIX(*pCreationTime);
		time_t lastAccessTime = FILETIME_TO_UNIX(*pLastAccessTime);
		time_t lastWriteTime = FILETIME_TO_UNIX(*pLastWriteTime);

		return Sandbox::ApplicationSandbox->SetFileTimes(absolutePath, creationTime, lastAccessTime, lastWriteTime);
	}

	int ICall::PsmFileGetPathInformation(const char* pszFileName, ScePssFileInformation_t* pFileInfo) {
		Logger::Debug(__FUNCTION__);

		if (pFileInfo == NULL || pszFileName == NULL)
			return PSM_ERROR_INVALID_PARAMETER;

		memset(pFileInfo, 0, sizeof(ScePssFileInformation_t));

		std::string relativePath = std::string(pszFileName);
		std::string absolutePath = Sandbox::ApplicationSandbox->AbsolutePath(relativePath);

		Logger::Debug("GetPathInfo: " + relativePath);

		if (!Sandbox::ApplicationSandbox->PathExist(absolutePath, false))
			return PSM_ERROR_NOT_FOUND;

		ScePssFileInformation_t fileinfo = Sandbox::ApplicationSandbox->Stat(absolutePath, relativePath);
		memcpy(pFileInfo, &fileinfo, sizeof(ScePssFileInformation_t));

		return PSM_ERROR_NO_ERROR;
	}
}
