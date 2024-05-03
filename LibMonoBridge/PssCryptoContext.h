#ifndef LIB_MONO_BRIDGE_PSS_CRYPTO_CONTEXT_H
#define LIB_MONO_BRIDGE_PSS_CRYPTO_CONTEXT_H 1

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct _PssCryptoContext {
		int handle;
		int valid;
		int size;
		int type;
	} PssCryptoContext;
#ifdef __cplusplus
}
#endif

#endif