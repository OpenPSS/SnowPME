#include <LibShared.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <PssCryptoCallbacks.h>
#include <PssCryptoSeek.h>
#include <PssCryptoContext.h>
#include <PssCrypto.h>
#include <mono/mono.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace Shared::Debug;
static PssCryptoCallbacks efuncs;

int ScePsmEdataMonoInit(PssCryptoCallbacks* edataFunctions) {
	Logger::Debug(">>>>>>>>>> ScePsmEdataMonoInit inside");
	if (edataFunctions != nullptr) {
		Logger::Debug(">>>>>>>>>> ScePsmEdataMonoInit Initializing");

		efuncs.eOpen = edataFunctions->eOpen;
		efuncs.eClose = edataFunctions->eClose;
		efuncs.eRead = edataFunctions->eRead;
		efuncs.eSeek = edataFunctions->eSeek;
	}

	return PSM_ERROR_NO_ERROR;
}

int mapToEdataSeek(int whence)
{
	// TODO: wtf are these seek whence? whats 0, where is 3???? 
	if (whence == SEEK_CUR)
		return PssCryptoSeekCur;
	if (whence == SEEK_END)
		return PssCryptoSeekEnd;
	return PssCryptoSeekSet;
}

long workaround_seek(PssCryptoContext* context, long offset, int whence)
{
	long totalSeeked = 0;
	int whencePss = mapToEdataSeek(whence);
	Logger::Debug("Seeking handle: " + std::to_string(context->handle) + ", offset: " + std::to_string(offset) + ", whence: " + std::to_string(whencePss) + "[" + std::to_string(whence) + "]");
	int res = efuncs.eSeek(context->handle, offset, whencePss, &totalSeeked);
	Logger::Debug("Seek returned: " + std::to_string(res) + ", size: "+std::to_string(totalSeeked)+" [" + std::to_string(totalSeeked) + "]");

	if (!res)
		return totalSeeked;

	Logger::Debug("scePsmEdataLseek failed with "+std::to_string(res));
	return (long)res;
}

int pss_crypto_open(PssCryptoContext* context, const char* path) {
	context->valid = 0;

	if(efuncs.eOpen(path, 1, 0, &context->handle, &context->type) == PSM_ERROR_NO_ERROR) {
		long sz = workaround_seek(context, 0x1, SEEK_END);
		workaround_seek(context, 0x0, SEEK_SET);
		Logger::Debug("Getting size: " + std::to_string(sz));
		context->size = sz + 1;
		context->valid = 1;
	}

	return context->valid;
}

char* pss_crypto_read(PssCryptoContext* context) {
	int totalRead = 0;
	char* ptr = new char[context->size];

	if (ptr == nullptr) {
		return nullptr;
	}

	if ((efuncs.eRead(context->handle, ptr, context->size, &totalRead) == PSM_ERROR_NO_ERROR) && context->size == totalRead) {
		return ptr;
	}
	
	delete[] ptr;
	return nullptr;
}

int pss_crypto_fread(PssCryptoContext* context, char* buffer, int bytes) {
	int totalRead = 0;
	efuncs.eRead(context->handle, buffer, bytes, &totalRead);
	return totalRead;
}

void pss_crypto_close(PssCryptoContext* context) {
	if (context->valid)
	{
		efuncs.eClose(context->handle);
		context->valid = 0;
	}
}
