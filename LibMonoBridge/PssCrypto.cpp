#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <PssCrypto.hpp>
#include <mono/mono.h>
#include <Sce/Pss/Core/Edata/PsmDrmLicense.hpp>
#include <Sce/Pss/Core/Edata/PsmDrm.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Edata;

int pss_crypto_open(PssCryptoContext* context, const char* path) {
	Logger::Debug(__FUNCTION__);
	Logger::Debug("Opening file: " + std::string(path));
	
	
	ScePsmDrmLicense licenseBuf;
	std::ifstream license = std::ifstream("Test/License/FAKE.RIF", std::ios::binary | std::ios::in);
	if (license.fail()) throw std::exception("didnt work");
	license.read((char*)&licenseBuf, sizeof(ScePsmDrmLicense));
	license.close();

	char gameKey[0x10];
	PsmDrm::scePsmDrmGetRifKey(&licenseBuf, gameKey, 0);


	if (context != nullptr) {
		memset(context, 0, sizeof(PssCryptoContext));
		EdataStream* stream = new EdataStream(std::string(path), std::ios::binary | std::ios::in, gameKey);
		ReturnErrorableAsBool(stream);

		context->handle = stream->Handle;
		context->size = stream->Filesize();
		context->type = SCE_PSS_FILE_FLAG_READONLY;
		context->valid = true;

		return true;
	}
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
