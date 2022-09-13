#ifndef LIB_PSM_PSMFRAMEBUFFER_H
#define LIB_PSM_PSMFRAMEBUFFER_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "TextureCubeFace.hpp"
using namespace std;

namespace Sce::PlayStation::Core::Graphics {
	class PsmFrameBuffer {
	public:
		static int Create(int *result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int SetColorTarget(int handle, int colorBuffer, int level, TextureCubeFace cubeFace, int *result);
		static int SetDepthTarget(int handle, int depthBuffer, int level, TextureCubeFace cubeFace, int *result);
	};
}
#endif
