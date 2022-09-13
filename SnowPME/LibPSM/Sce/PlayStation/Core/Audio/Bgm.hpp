#ifndef LIB_PSM_BGM_H
#define LIB_PSM_BGM_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Audio {
	class Bgm {
	public:
		static int NewFromFilename(string filename, int* handle);
		static int NewFromFileImage(byte* fileImage, int* handle);
		static int ReleaseNative(int handle);
		static int CreatePlayerNative(int handle, int* playerHandle);
	};
}
#endif
