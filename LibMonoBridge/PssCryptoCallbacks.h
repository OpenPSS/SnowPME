#ifndef LIB_MONO_BRIDGE_PSS_CRYPTO_CALLBACKS_H
#define LIB_MONO_BRIDGE_PSS_CRYPTO_CALLBACKS_H 1
#include <PssCryptoContext.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*edataOpenFunc)(const char* path, int flags, int mode, int* handle, int* type);
typedef int (*edataReadFunc)(int handle, void* buffer, int toRead, int* totalRead);
typedef void (*edataCloseFunc)(int handle);
typedef int (*edataSeekFunc)(int handle, long offset, int whence, long* totalSeeked);

typedef struct _edata_callbacks {
	edataOpenFunc eOpen;
	edataCloseFunc eClose;
	edataReadFunc eRead;
	edataSeekFunc eSeek;
} PssCryptoCallbacks;

#ifdef __cplusplus
}
#endif

#endif