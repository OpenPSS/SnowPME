#ifndef LIB_MONO_BRIDGE_PSS_CRYPTO_H
#define LIB_MONO_BRIDGE_PSS_CRYPTO_H 1
#include <PssCrypytoContext.h>

#ifdef __cplusplus
extern "C" {
#endif
	int pss_crypto_open(PssCryptoContext* context, const char* path);
	char* pss_crypto_read(PssCryptoContext* context);
	int pss_crypto_fread(PssCryptoContext* context, char* buffer, int bytes);
	void pss_crypto_close(PssCryptoContext* context);
#ifdef __cplusplus
}
#endif

#endif