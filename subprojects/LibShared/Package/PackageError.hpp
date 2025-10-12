/*
* PKG extraction code based on
* Real-Package-Installer by LiEnby.
* https://silica.codes/Li/real-package-installer/
*/

#ifndef SHARED_PACKAGE_ERROR_H 
#define SHARED_PACKAGE_ERROR_H 1
#include <cstdint>

enum PackageError : int32_t {
	PKG_ERROR_NO_ERROR = 0,
	PKG_ERROR_OPEN_FAILED = -1,
	PKG_ERROR_INVALID_PACKAGE_TYPE = -2,
	PKG_ERROR_UNKNOWN_KEY = -3,
	PKG_ERROR_INVALID_MAGIC = -4,
	PKG_ERROR_READ_SIZE_NO_MATCH = -5,
	PKG_ERROR_INVALID_CONTENT_TYPE = -6,
	PKG_ERROR_INVALID_EXT_MAGIC = -7,
	PKG_ERROR_FILE_NOT_FOUND = -8
};

#endif