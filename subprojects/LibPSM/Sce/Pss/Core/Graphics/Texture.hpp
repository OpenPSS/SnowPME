#ifndef LIB_PSS_TEXTURE_H
#define LIB_PSS_TEXTURE_H 1
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class Texture : public PixelBuffer {
	private:
		static uint8_t g_image[0x8000];
	public:

		int ActiveStateChanged(bool state);
		int SetPixels(int mipmapLevel, TextureCubeFace cubeFace, uint8_t* pixels, size_t pixelsSize, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh);

		Texture() = default;
		virtual ~Texture() = default;
	};
}

#endif
