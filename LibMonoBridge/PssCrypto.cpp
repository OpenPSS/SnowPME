#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <PssCrypto.hpp>
#include <mono/mono.h>

#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Edata/EdataStream.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Edata;


int pss_crypto_open(PssCryptoContext* context, const char* path) {
	Logger::Debug(__FUNCTION__);
	Logger::Debug("file: " + std::string(path));

	if (context != nullptr) {
		memset(context, 0, sizeof(PssCryptoContext));

		EdataStream* stream = new EdataStream(std::string(path), std::ios::binary | std::ios::in, Sandbox::ApplicationSandbox->GameDrmProvider, nullptr);
		ReturnErrorableAsBool(stream);

		context->handle = stream->Handle;
		context->size = stream->Filesize();
		context->type = SCE_PSS_FILE_FLAG_READONLY;
		context->valid = true;

		return true;
	}
	Logger::Debug("file not found .");
	return false;
}

char* pss_crypto_read(PssCryptoContext* context) {
	Logger::Debug(__FUNCTION__);
	if (context != nullptr) {
		if (Handles::IsValid(context->handle)) {
			EdataStream* str = (EdataStream*)Handles::GetHandle(context->handle);

			char* data = new char[context->size];
			str->Read(data, context->size);
			return data;
		}
		return nullptr;
	}
	return nullptr;
}

int pss_crypto_fread(PssCryptoContext* context, char* buffer, int bytes) {
	Logger::Debug(__FUNCTION__);
	if (context != nullptr) {
		if (Handles::IsValid(context->handle)) {
			EdataStream* str = (EdataStream*)Handles::GetHandle(context->handle);

			return str->Read(buffer, bytes);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	return PSM_ERROR_COMMON_ARGUMENT_NULL;
}

void pss_crypto_close(PssCryptoContext* context) {
	Logger::Debug(__FUNCTION__);
	if (context != nullptr) {
		if (Handles::IsValid(context->handle)) {
			EdataStream* str = (EdataStream*)Handles::GetHandle(context->handle);
			context->handle = Handles::NoHandle;
			context->valid = false;
			delete str;
		}
	}
}
