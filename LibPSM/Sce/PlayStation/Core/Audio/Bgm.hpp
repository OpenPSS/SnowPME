#ifndef LIB_PSM_BGM_H
#define LIB_PSM_BGM_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Audio {
	class Bgm {
	public:
		static int NewFromFilename(std::string filename, int* handle);
		static int NewFromFileImage(uint8_t* fileImage, int* handle);
		static int ReleaseNative(int handle);
		static int CreatePlayerNative(int handle, int* playerHandle);
	};
}
#endif
