#ifndef LIB_MONO_BRIDGE_PSS_CRYPTO_SEEK_H
#define LIB_MONO_BRIDGE_PSS_CRYPTO_SEEK_H 1

#ifdef __cplusplus
extern "C" {
#endif
	typedef enum _PssCryptoSeek {
		PssCryptoSeekCur = 2,
		PssCryptoSeekEnd = 4,
		PssCryptoSeekSet = 1
	} PssCryptoSeek;
#ifdef __cplusplus
}
#endif
#endif