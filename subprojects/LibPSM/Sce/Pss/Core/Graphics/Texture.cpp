#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <LibShared.hpp>

#include <glad/glad.h>

using namespace Shared::Debug;
using namespace Shared::String;
namespace Sce::Pss::Core::Graphics {


	int Texture::ActiveStateChanged(bool state) {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

	int Texture::SetPixels(int mipmapLevel, TextureCubeFace cubeFace, int* pixels, size_t pixelsSize, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh)
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

		if (format != this->Format && (format != PixelFormat::Rgba || format >= PixelFormat::Dxt1)) {
			ExceptionInfo::AddMessage("Incompatible format with pixel buffer\n");
			return PSM_ERROR_COMMON_NOT_SUPPORTED;
		}

		int bpp = PixelBuffer::GetFormatBitsPerPixel(format);

		int sizeInBytes = PixelBuffer::CalculateImageArraySizeInBytes(format, bpp, dw, dh);

		if (pitch == NULL)
			pitch = sizeInBytes;

		int mipmapWidth = this->GetMipmapWidth(mipmapLevel);
		int mipmapHeight = this->GetMipmapHeight(mipmapLevel);

		if (dx < 0 || dy < 0 || dh < 0 || dw < 0 || offset < 0 || dw + dx > mipmapWidth || dh + dy > mipmapHeight || pitch < sizeInBytes)
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;


		// TODO: double check this, it doesnt seem right;

		/*if (offset + sizeInBytes * pitch * (dh - 1) > pixelsSize) {
			ExceptionInfo::AddMessage("Pixel array is smaller than required\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if ((pitch | offset) != 0) {
			ExceptionInfo::AddMessage("Offset or pitch is not aligned properly\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}*/

		if (PixelBuffer::IsFormatDxt(format)) {
			UNIMPLEMENTED_MSG("SetPixels, format > PixelFormat::Dxt1");
		}

		if (dw != 0 && dh != 0) {
			int* pixelPtr = pixels + offset;

			//TODO: int* ptr = g_framebuffer_related
			//TODO: implement DXT

			int start = 1;
			GLenum glPixType = this->GetDeviceFaceTarget(cubeFace);
			GLenum formatComponent = OpenGL::GetTextureFormatComponent(this->Format);
			GLenum formatType = OpenGL::GetTextureFormatType(this->Format);
			Texture* prev = OpenGL::SetTexture(this);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			UNIMPLEMENTED_MSG("pixel set loop");

			OpenGL::SetTexture(prev);
		}

		return PSM_ERROR_NO_ERROR;
	}

}