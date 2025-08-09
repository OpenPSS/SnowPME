/*
* PKG extraction code based on
* Real-Package-Installer by LiEnby.
* https://silica.codes/Li/real-package-installer/src/branch/main
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "io.h"
#include "err.h"

#include "sceIo.hpp"
#include <filesystem>

int file_exist(const char* path) {
	return std::filesystem::exists(path);
}

uint64_t get_file_size(const char* filepath) {
	return std::filesystem::file_size(filepath);
}

int read_file(const char* path, void* data, size_t size) {
	
	int ret = 0;
	SceUID fd = sceIoOpen(path, SCE_O_RDONLY, 0777);
	if(fd > 0) {
		ret = sceIoRead(fd, data, size);
		if(ret < 0) goto error;
		if(ret != size) ERROR(-1);
	}
	
error:
	sceIoClose(fd);
	return ret;
	
}

int write_file(const char* path, const void* data, size_t size) {
	char outdir[MAX_PATH];
	int ret = 0;

	// create directory for file if it doesnt exist already.
	extract_dirname(path, outdir, sizeof(outdir));
	make_directories(outdir);
	
	SceUID wfd = sceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT, 0777);
	if(wfd > 0) {
		ret = sceIoWrite(wfd, data, size);
		if(ret < 0) goto error;
		if(ret != size) ERROR(-1);
	}
	
error:
	sceIoClose(wfd);
	return ret;
	
}

int copy_file(const char* path, const char* new_path) {
	if (std::filesystem::copy_file(path, new_path))
		return 0;
	else
		return -1;
}

int extract_dirname(const char* path, char* dirname, int dirname_length) {
	strncpy(dirname, path, dirname_length);
	
	
	int lastSlash = 0;
	for(int i = 0; i < strlen(path); i++) {
		if(path[i] == '/' || path[i] == '\\') lastSlash = i;
	}
	
	dirname[lastSlash] = 0;
	return lastSlash;
}

void make_directories(const char* path) {
	if(file_exist(path)) return;
	
	char dirname[MAX_PATH];
	memset(dirname, 0x00, sizeof(dirname));
	

	for(int i = 0; i < strlen(path); i++) {
		if(path[i] == '/' || path[i] == '\\') {
			memset(dirname, 0, sizeof(dirname));
			strncpy(dirname, path, i);

			if(!file_exist(dirname)){
				std::filesystem::create_directory(dirname);
			}	
		}
	}
	
	std::filesystem::create_directory(dirname);
	
}