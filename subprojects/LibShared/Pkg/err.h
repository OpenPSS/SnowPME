/*
* PKG extraction code based on
* Real-Package-Installer by LiEnby.
* https://silica.codes/Li/real-package-installer/src/branch/main
*/

#define ERROR(x) { ret = x; goto error; }

#define CHECK_ERROR(x) \
	do { \
		int ret = (int)(x);\
		if(ret < 0) { \
			return ret; \
		} \
	} while(0);
