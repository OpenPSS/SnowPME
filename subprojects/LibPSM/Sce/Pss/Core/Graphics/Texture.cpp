#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormats.hpp>
#include <LibShared.hpp>

#include <glad/glad.h>

using namespace Shared::Debug;
using namespace Shared::String;
namespace Sce::Pss::Core::Graphics {
	uint8_t Texture::g_image[0x8000] = { 0 };

	int Texture::ActiveStateChanged(bool state) {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

	inline uint16_t make_rgba4444(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		PixelFormats::Rgba4444 rgba = { .r = red, .g = green, .b = blue, .a = alpha };
		return *(uint16_t*)(&rgba);
	}
	inline uint16_t make_rgba5551(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		PixelFormats::Rgba5551 rgba = { .r = red, .g = green, .b = blue, .a = alpha };
		return *(uint16_t*)(&rgba);
	}
	inline uint16_t make_rgb565(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		PixelFormats::Rgb565 rgb = { .r = red, .g = green, .b = blue};
		return *(uint16_t*)(&rgb);
	}

	inline int write_data(int dw, uint8_t* dstBuf, uint8_t* srcBuf, PixelFormat format) {
		uint16_t (*handler) (uint8_t r, uint8_t g, uint8_t b, uint8_t a) = nullptr;

		switch (format) {
		case PixelFormat::RgbaH:
			UNIMPLEMENTED_MSG("PixelFormat::RgbaH");
			break;
		case PixelFormat::Rgba4444:
			handler = make_rgba4444;
			break;
		case PixelFormat::Rgba5551:
			handler = make_rgba5551;
			break;
		case PixelFormat::Rgb565:
			handler = make_rgb565;
			break;
		case PixelFormat::LuminanceAlpha:
			UNIMPLEMENTED_MSG("PixelFormat::LuminanceAlpha");
			break;
		case PixelFormat::LuminanceAlphaH:
			UNIMPLEMENTED_MSG("PixelFormat::LuminanceAlphaH");
			break;
		case PixelFormat::LuminanceH:
			UNIMPLEMENTED_MSG("PixelFormat::LuminanceH");
			break;
		case PixelFormat::Alpha:
			UNIMPLEMENTED_MSG("PixelFormat::Alpha");
			break;
		case PixelFormat::AlphaH:
			UNIMPLEMENTED_MSG("PixelFormat::AlphaH");
			break;
		}

		// 2 byte wide pixels ...
		if (handler != nullptr) {
			if (dw > 0) {
				PixelFormats::Rgba* rgbaSrc = reinterpret_cast<PixelFormats::Rgba*>(srcBuf);
				uint16_t* rgbaDst = reinterpret_cast<uint16_t*>(dstBuf);

				for (;dw > 0; dw--) {

					*rgbaDst = handler(rgbaSrc->r, rgbaSrc->g, rgbaSrc->b, rgbaSrc->a);
					
					// move to next part 
					rgbaDst++;
					rgbaSrc++;
				}
			}
		}

		return PSM_ERROR_NO_ERROR;
	}

	int Texture::SetPixels(int mipmapLevel, TextureCubeFace cubeFace, uint8_t* pixels, size_t pixelsSize, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh)
	{		
		if (pixels == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (mipmapLevel < 0 || mipmapLevel >= this->mipmapLevel)
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		if (cubeFace > TextureCubeFace::NegativeZ)
			return PSM_ERROR_COMMON_ARGUMENT;
		if (format > PixelFormat::Dxt5)
			return PSM_ERROR_COMMON_ARGUMENT;
		if (format == PixelFormat::None)
			format = this->Format;

		bool formatMatches = format != this->Format;

		if (formatMatches && (format != PixelFormat::Rgba || format >= PixelFormat::Dxt1)) {
			ExceptionInfo::AddMessage("Incompatible format with pixel buffer\n");
			return PSM_ERROR_COMMON_NOT_SUPPORTED;
		}

		int bpp = PixelBuffer::GetFormatBitsPerPixel(format);
		int wBytesTotal = TO_BYTES_C(bpp * (PixelBuffer::AdjValueForDxt(format, dw)));

		if (pitch == NULL)
			pitch = wBytesTotal;

		int mipmapWidth = this->GetMipmapWidth(mipmapLevel);
		int mipmapHeight = this->GetMipmapHeight(mipmapLevel);

		if (dx < 0 || dy < 0 || dh < 0 || dw < 0 || offset < 0 || dw + dx > mipmapWidth || dh + dy > mipmapHeight || pitch < wBytesTotal) {
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}
		
		// TODO: cleanup this if statement
		if (offset + wBytesTotal * (PixelBuffer::GetDxtMultiplier(format) + 1) + pitch * (~PixelBuffer::GetDxtMultiplier(format) & (dh - 1)) > pixelsSize) {
			ExceptionInfo::AddMessage("Pixel array is smaller than required\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		
		if ( (TO_BYTES_C(bpp) & (pitch | offset)) != 0) {
			ExceptionInfo::AddMessage("Offset or pitch is not aligned properly\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}


		if (PixelBuffer::IsFormatDxt(format)) {
			UNIMPLEMENTED_MSG("SetPixels, format > PixelFormat::Dxt1");
			// TODO: cleanup this if statement
			int adjDh = 0;
			if ((dw & 3) != 0 && dw + dx != mipmapWidth || (adjDh = dh, (dh & 3) != 0) && dy + dh != mipmapHeight || ((dy | dx) & 3) != 0)
			{
				ExceptionInfo::AddMessage("Destination dx/dy/dw/dh is not aligned properly\n");
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}
			dh = adjDh;
		}

		if (dw != 0 && dh != 0) {
			uint8_t* p = Texture::g_image;

			// if the format matches, then set the current ptr to the pixelPtr
			if (!formatMatches)
				p = &pixels[offset];

			int end = 1;
			int yoffset = PixelBuffer::GetDxtMultiplier(format) + 1;

			// TODO: why? 
			if (formatMatches || pitch != wBytesTotal) {
				end = (PixelBuffer::GetDxtMultiplier(format) + dh) / yoffset;
				dh -= yoffset * (end - 1);
			}


			GLenum glPixType = this->GetDeviceFaceTarget(cubeFace);
			GLenum formatComponent = OpenGL::GetTextureFormatComponent(this->Format);
			GLenum formatType = OpenGL::GetTextureFormatType(this->Format);
			Texture* prev = OpenGL::SetTexture(this);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			if (end > 0) {
				for (int i = end; i--; i < 0) {
					if (PixelBuffer::IsFormatDxt(format)) {
						int adjHeight = (i <= 0) ? 4 : dh;
						int adjSize = wBytesTotal * (dh + (3 & -4));

						glCompressedTexSubImage2D(glPixType, mipmapLevel, dx, dy, dw, adjHeight, formatComponent, adjSize, p);

						p += pitch;
						dy += 4;
					}
					else {
						if (formatMatches) {
							write_data(dw, g_image, &pixels[offset], this->Format);
						}

						glTexSubImage2D(glPixType, mipmapLevel, dx, dy++, dw, dh, formatComponent, formatType, p);
						p += formatMatches ? 0 : pitch;
					}
				}
			}

			OpenGL::SetTexture(prev);
		}

		return PSM_ERROR_NO_ERROR;
	}

}