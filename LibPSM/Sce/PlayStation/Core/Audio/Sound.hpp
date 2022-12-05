#ifndef LIB_PSM_SOUND_H
#define LIB_PSM_SOUND_H 1
#include <cstdint>
#include <mono/mono.h>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Audio {
	class Sound {
	public:
		static int NewFromFilename(MonoString* filename, int *handle);
		static int NewFromFileImage(MonoArray* fileImage, int *handle);
		static int ReleaseNative(int handle);
		static int CreatePlayerNative(int handle, int *playerHandle);
	};
}
#endif
