#ifndef LIB_PSM_PSMPIXELBUFFER_H
#define LIB_PSM_PSMPIXELBUFFER_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "PixelBufferType.hpp"
#include "PixelFormat.hpp"
#include "PixelBufferOption.hpp"
#include "InternalOption.hpp"

using namespace std;

namespace Sce::PlayStation::Core::Graphics {
	class PsmPixelBuffer {
	public:
		static int Create(PixelBufferType type, int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption option2, int *result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int GetInfo(int handle, PixelBufferType *type, int *width, int *height, int *level, PixelFormat *format, PixelBufferOption *option);
	};
}
#endif
