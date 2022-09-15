#ifndef LIB_PSM_SOUND_H
#define LIB_PSM_SOUND_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Audio {
	class Sound {
	public:
		static int NewFromFilename(std::string filename, int *handle);
		static int NewFromFileImage(std::byte* fileImage, int *handle);
		static int ReleaseNative(int handle);
		static int CreatePlayerNative(int handle, int *playerHandle);
	};
}
#endif