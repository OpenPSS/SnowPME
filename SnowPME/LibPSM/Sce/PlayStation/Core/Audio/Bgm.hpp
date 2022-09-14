#ifndef LIB_PSM_BGM_H
#define LIB_PSM_BGM_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Audio {
	class Bgm {
	public:
		static int NewFromFilename(std::string filename, int* handle);
		static int NewFromFileImage(std::byte* fileImage, int* handle);
		static int ReleaseNative(int handle);
		static int CreatePlayerNative(int handle, int* playerHandle);
	};
}
#endif
