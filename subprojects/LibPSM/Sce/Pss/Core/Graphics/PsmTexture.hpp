#ifndef LIB_PSS_PSMTEXTURE_H
#define LIB_PSS_PSMTEXTURE_H 1
#include <cstdint>

#include <string>
#include <iostream>

#include <mono/mono.h>

#include <Sce/Pss/Core/Graphics/PixelBufferType.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/TextureWrap.hpp>
#include <Sce/Pss/Core/Graphics/TextureFilter.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/Features.hpp>


namespace Sce::Pss::Core::Graphics {
	class PsmTexture : public PsmMutexObject<PsmTexture> {
	public:
		static int FromFile(PixelBufferType type, MonoString* fileName, bool mipmap, PixelFormat format, int *result);
		static int FromImage(PixelBufferType type, MonoArray* fileImage, bool mipmap, PixelFormat format, int *result);
		static int SetFilter(int handle, TextureFilter *filter);
		static int SetWrap(int handle, TextureWrap *filter);
		static int SetMaxAnisotropy(int handle, float anisotropy);
		static int SetPixels(int handle, int level, TextureCubeFace cubeFace, MonoArray *pixels, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh);
		static int GenerateMipmap(int handle);
	};
}
#endif
