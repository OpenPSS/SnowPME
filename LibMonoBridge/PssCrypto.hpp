#ifndef LIB_MONO_BRIDGE_PSS_CRYPTO_H
#define LIB_MONO_BRIDGE_PSS_CRYPTO_H 1

extern "C" {
	typedef struct _PssCryptoContext {
		int handle;
		int valid;
		int size;
		int type;
	} PssCryptoContext;

	int pss_crypto_open(PssCryptoContext* context, const char* path);
	char* pss_crypto_read(PssCryptoContext* context);
	int pss_crypto_fread(PssCryptoContext* context, char* buffer, int bytes);
	void pss_crypto_close(PssCryptoContext* context);
}

#endif