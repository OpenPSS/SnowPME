/*
* PKG extraction code based on
* Real-PackageExtractor-Installer by LiEnby.
* https://silica.codes/Li/real-PackageExtractor-installer/
*/

#ifndef SHARED_PACKAGE_ERROR_H 
#define SHARED_PACKAGE_ERROR_H 1

#include <cstdint>

#define ERROR(x) { ret = x; goto error; }

#define CHECK_ERROR(x) \
	do { \
		int ret = (int)(x);\
		if(ret < 0) { \
			return ret; \
		} \
	} while(0);

enum PackageError : int32_t {
	PKG_ERROR_NO_ERROR = 0,
	PKG_ERROR_OPEN_FAILED = -1,
	PKG_ERROR_INVALID_PACKAGE_TYPE = -2,
	PKG_ERROR_UNKNOWN_KEY = -3,
	PKG_ERROR_INVALID_MAGIC = -4,
	PKG_ERROR_READ_SIZE_NO_MATCH = -5,
	PKG_ERROR_INVALID_CONTENT_TYPE = -6,
	PKG_ERROR_INVALID_EXT_MAGIC = -7
};

#endif