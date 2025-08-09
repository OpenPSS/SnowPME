/*
* PKG extraction code based on
* Real-Package-Installer by LiEnby.
* https://silica.codes/Li/real-package-installer/src/branch/main
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IO_H
#define IO_H 1

#define MAX_PATH (260)

#include <stddef.h>
#include <stdint.h>
#include "sceTypes.hpp"

	typedef struct SearchFilter {
		uint64_t max_filesize;
		uint8_t file_only;
		char match_extension[MAX_PATH];
	} SearchFilter;

	uint64_t get_file_size(const char* filepath);
	int file_exist(const char* path);
	int write_file(const char* path, const void* data, size_t size);
	int read_file(const char* path, void* data, size_t size);
	int copy_file(const char* path, const char* new_path);

	int extract_dirname(const char* path, char* dirname, int dirname_length);
	void make_directories(const char* path);


#ifdef __cplusplus
}
#endif

#endif