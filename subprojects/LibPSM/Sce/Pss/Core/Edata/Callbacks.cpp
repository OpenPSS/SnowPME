#include <Sce/Pss/Core/Edata/Callbacks.hpp>
#include <Sce/Pss/Core/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>

#include <LibMonoBridge.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Edata {
	int Callbacks::EdataOpen(const char* path, int flags, int mode, int* handle, int* type) {
		Logger::Debug("edata open file: " + std::string(path));

		if (handle != nullptr && type != nullptr) {
			EdataStream* stream = new EdataStream(std::string(path), std::ios::binary | std::ios::in, Sandbox::GetUniqueObject()->GameDrmProvider, nullptr);
			ReturnErrorable(stream);

			*handle = stream->Handle;

			*type = SCE_PSS_FILE_FLAG_READONLY;
			if (stream->FileEncrypted)
				*type |= SCE_PSS_FILE_FLAG_ENCRYPTED;

			return PSM_ERROR_NO_ERROR;
		}


		return PSM_ERROR_COMMON_ARGUMENT_NULL;
	}
	int Callbacks::EdataRead(int handle, void* buffer, int toRead, int* totalRead) {
		if (Handles::IsValid(handle) && totalRead != nullptr) {
			EdataStream* stream = Handles::Get<EdataStream>(handle);

			*totalRead = stream->Read((char*)buffer, toRead);

			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int Callbacks::EdataSeek(int handle, long offset, int whence, long* totalSeeked) {
		if (Handles::IsValid(handle) && totalSeeked != nullptr) {
			EdataStream* stream = Handles::Get<EdataStream>(handle);

			ScePssFileSeekType_t whenceType = SCE_PSS_FILE_SEEK_TYPE_BEGIN;
			if (whence == PssCryptoSeekCur)
				whenceType = SCE_PSS_FILE_SEEK_TYPE_CURRENT;
			if (whence == PssCryptoSeekEnd)
				whenceType = SCE_PSS_FILE_SEEK_TYPE_END;
			else if (whence == PssCryptoSeekSet)
				whenceType = SCE_PSS_FILE_SEEK_TYPE_BEGIN;

			// get current position
			uint64_t startPos = stream->Tell();
			int err = stream->Seek(offset, whenceType);
			uint64_t endPos = stream->Tell();

			if (err == PSM_ERROR_NO_ERROR) {
				if (startPos >= endPos)
					*totalSeeked = (long)(startPos - endPos);
				else if (endPos >= startPos)
					*totalSeeked = (long)(endPos - startPos);
			}
			else {
				return err;
			}
		}
		else {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		return PSM_ERROR_NO_ERROR;
	}
	void Callbacks::EdataClose(int handle) {
		if (Handles::IsValid(handle)) {
			EdataStream* str = Handles::Get<EdataStream>(handle);
			delete str;
		}
	}
}