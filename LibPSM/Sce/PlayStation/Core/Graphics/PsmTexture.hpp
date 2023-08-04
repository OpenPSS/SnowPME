#ifndef LIB_PSM_PSMTEXTURE_H
#define LIB_PSM_PSMTEXTURE_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include <mono/mono.h>

#include "PixelBufferType.hpp"
#include "TextureCubeFace.hpp"
#include "PixelFormat.hpp"
#include "TextureWrap.hpp"
#include "TextureFilter.hpp"


namespace Sce::PlayStation::Core::Graphics {
	class PsmTexture {
	public:
		static int FromFile(PixelBufferType type, MonoString* fileName, bool mipmap, PixelFormat format, int *result);
		static int FromImage(PixelBufferType type, MonoArray* fileImage, bool mipmap, PixelFormat format, int *result);
		static int SetFilter(int handle, TextureFilter *filter);
		static int SetWrap(int handle, TextureWrap *filter);
		static int SetMaxAnisotropy(int handle, float anisotropy);
		static int SetPixels(int handle, int level, TextureCubeFace cubeFace, int *pixels, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh);
		static int GenerateMipmap(int handle);
	};
}
#endif
