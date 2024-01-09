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
	
	/*
	ScePsmDrmLicense licenseBuf;
	std::ifstream license = std::ifstream("Test/License/FAKE.RIF", std::ios::binary | std::ios::in);
	if (license.fail()) throw std::exception("didnt work");
	license.read((char*)&licenseBuf, sizeof(ScePsmDrmLicense));
	license.close();

	char gameKey[0x10];
	PsmDrm::scePsmDrmGetRifKey(&licenseBuf, gameKey, 0);


	if (context != nullptr) {
		EdataStream* stream = new EdataStream(std::string(path), gameKey);

	}*/

	if (context != nullptr) {
		std::fstream* str = new std::fstream(path, std::ios::in | std::ios::binary);
		memset(context, 0x00, sizeof(PssCryptoContext));

		if (!str->fail()) {
			context->handle = Handles::CreateHandle((uintptr_t)str);
			context->size = std::filesystem::file_size(path);
			context->type = SCE_PSS_FILE_FLAG_ENCRYPTED;
			context->valid = true;

			return true;
		}
		Logger::Debug("Failed to open file.");
		context->valid = false;
		return false;
	}

	return false;
}

char* pss_crypto_read(PssCryptoContext* context) {
	Logger::Debug(__FUNCTION__);
	if (context != nullptr) {
		if (Handles::IsValid(context->handle)) {
			std::fstream* str = (std::fstream*)Handles::GetHandle(context->handle);

			char* data = new char[context->size];
			str->read(data, context->size);
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
			std::fstream* str = (std::fstream*)Handles::GetHandle(context->handle);

			str->read(buffer, bytes);
			return (int)str->gcount();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	return PSM_ERROR_COMMON_ARGUMENT_NULL;
}

void pss_crypto_close(PssCryptoContext* context) {
	Logger::Debug(__FUNCTION__);
	if (context != nullptr) {
		if (Handles::IsValid(context->handle)) {
			std::fstream* str = (std::fstream*)Handles::GetHandle(context->handle);
			str->close();
			Handles::DeleteHandle(context->handle);
			context->handle = Handles::NoHandle;
			context->valid = false;
			delete str;
		}
	}
}
