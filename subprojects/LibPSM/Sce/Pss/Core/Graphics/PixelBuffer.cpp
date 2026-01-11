#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferType.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferOption.hpp>
#include <Sce/Pss/Core/Features.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormats.hpp>
#include <LibShared.hpp>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Io;

using namespace Shared::Debug;
using namespace Shared::String;

namespace Sce::Pss::Core::Graphics {

	
	uint32_t PixelBuffer::SetError(int error) {
		if (error == PSM_ERROR_NO_ERROR) return true;

		if (!this->filename.empty()) {
			ExceptionInfo::AddMessage("Could not load file '" + this->filename + "'\n");
		}
		Errorable::SetError(error);


		return PSM_ERROR_NO_ERROR;
	}
	int PixelBuffer::GetInfo(PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option) {
		*type = this->type;
		*width = this->width;
		*height = this->height;
		*level = this->mipmapLevel;
		*format = this->Format;
		*option = this->Option;
		return PSM_ERROR_NO_ERROR;
	}

	int PixelBuffer::LoadImage(uint8_t* data, uint64_t dataLen, int mipmap, PixelFormat format) {
		return PSM_ERROR_NO_ERROR;
	}

	bool PixelBuffer::GetFormatIsValid(PixelFormat format) {
		return format <= PixelFormat::Depth24Stencil8;
	}

	bool PixelBuffer::CheckFormatError(PixelFormat format, PixelBufferOption option) {
		if (!this->GetFormatIsValid(format) || (option & 0xFFFFFFFE) != PixelBufferOption::None) {
			return this->SetError(PSM_ERROR_COMMON_ARGUMENT);
		}
		else {
			return true;
		}
	}
	bool PixelBuffer::CheckSizeError(int width, int height, int min, int max) {
		if (width > max || width < min) {
			return this->SetError(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
		}

		if (height > max || height < min) {
			return this->SetError(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
		}

		return true;
	}

	bool PixelBuffer::CheckFormatSizeError(PixelFormat format, int width, int height) {
		// if it is not a DXT texture, or the texture is not a power of two,
		// then this check succeeds, otherwise it fails;

		if (format < PixelFormat::Dxt1 || PixelBuffer::CheckPowerOfTwo(width, height))
			return true;

		ExceptionInfo::AddMessage("Unsupported size for compressed texture\n");
		return PixelBuffer::SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
	}

	bool PixelBuffer::CheckPowerOfTwo(int width, int height) {
		return (IS_POW_2(width) && IS_POW_2(height));
	}

	bool PixelBuffer::CheckGLError() {
		GLenum err = glGetError();
		if (err == GL_NO_ERROR) {
			return true;
		}
		if (err == GL_OUT_OF_MEMORY) {
			return this->SetError(PSM_ERROR_COMMON_OUT_OF_MEMORY);
		}

		ExceptionInfo::AddMessage("Unsupported format on this device\n");
		return this->SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
	}

	bool PixelBuffer::AllocCache(InternalOption opt) {
		if ((opt & InternalOption::SystemResource) != InternalOption::None)
			return false;

		// NOTE : 
		// on android this actually mallocs;
		// on win32 & vita psm.exe it does a fake malloc instead ??
		// what???
		// i am going to assume this is an SDK2.00 thing

		bool success = HeapAllocator::fake_malloc(this->imageSize);

		if (success) {
			return true;
		}
		else {
			return this->SetError(PSM_ERROR_COMMON_OUT_OF_MEMORY);
		}
	}

	int PixelBuffer::GetMipmapHeight(int level) {
		int mmh = this->height >> level;

		if (mmh <= 0)
			return mmh > 0;
		return mmh;
	}

	int PixelBuffer::GetMipmapWidth(int level) {
		int mmw = this->width >> level;

		if (mmw <= 0)
			return mmw > 0;
		return mmw;
	}

	bool PixelBuffer::GetFormatHasDepth(PixelFormat format) {
		switch (format) {
			case PixelFormat::None:
				return false;
			case PixelFormat::Rgba:
				return false;
			case PixelFormat::RgbaH:
				return false;
			case PixelFormat::Rgba4444:
				return false;
			case PixelFormat::Rgba5551:
				return false;
			case PixelFormat::Rgb565:
				return false;
			case PixelFormat::LuminanceAlpha:
				return false;
			case PixelFormat::LuminanceAlphaH:
				return false;
			case PixelFormat::Luminance:
				return false;
			case PixelFormat::LuminanceH:
				return false;
			case PixelFormat::Alpha:
				return false;
			case PixelFormat::AlphaH:
				return false;
			case PixelFormat::Depth16:
				return true;
			case PixelFormat::Depth24:
				return true;
			case PixelFormat::Depth16Stencil8:
				return true;
			case PixelFormat::Depth24Stencil8:
				return true;
			case PixelFormat::Dxt1:
				return false;
			case PixelFormat::Dxt2:
				return false;
			case PixelFormat::Dxt3:
				return false;
			case PixelFormat::Dxt4:
				return false;
			case PixelFormat::Dxt5:
				return false;
		}
		UNREACHABLE();
	}

	bool PixelBuffer::GetFormatHasRgb(PixelFormat format) {
		switch (format) {
			case PixelFormat::None:
				return false;
			case PixelFormat::Rgba:
				return true;
			case PixelFormat::RgbaH:
				return true;
			case PixelFormat::Rgba4444:
				return true;
			case PixelFormat::Rgba5551:
				return true;
			case PixelFormat::Rgb565:
				return true;
			case PixelFormat::LuminanceAlpha:
				return false;
			case PixelFormat::LuminanceAlphaH:
				return false;
			case PixelFormat::Luminance:
				return false;
			case PixelFormat::LuminanceH:
				return false;
			case PixelFormat::Alpha:
				return false;
			case PixelFormat::AlphaH:
				return false;
			case PixelFormat::Depth16:
				return false;
			case PixelFormat::Depth24:
				return false;
			case PixelFormat::Depth16Stencil8:
				return false;
			case PixelFormat::Depth24Stencil8:
				return false;
			case PixelFormat::Dxt1:
				return true;
			case PixelFormat::Dxt2:
				return true;
			case PixelFormat::Dxt3:
				return true;
			case PixelFormat::Dxt4:
				return true;
			case PixelFormat::Dxt5:
				return true;
		}
		
		UNREACHABLE();
	}

	bool PixelBuffer::GetFormatHasHalfFloat(PixelFormat format) {
		switch (format) {
			case PixelFormat::None:
				return false;
			case PixelFormat::Rgba:
				return false;
			case PixelFormat::RgbaH:
				return true;
			case PixelFormat::Rgba4444:
				return false;
			case PixelFormat::Rgba5551:
				return false;
			case PixelFormat::Rgb565:
				return false;
			case PixelFormat::LuminanceAlpha:
				return false;
			case PixelFormat::LuminanceAlphaH:
				return true;
			case PixelFormat::Luminance:
				return false;
			case PixelFormat::LuminanceH:
				return true;
			case PixelFormat::Alpha:
				return false;
			case PixelFormat::AlphaH:
				return true;
			case PixelFormat::Depth16:
				return false;
			case PixelFormat::Depth24:
				return false;
			case PixelFormat::Depth16Stencil8:
				return false;
			case PixelFormat::Depth24Stencil8:
				return false;
			case PixelFormat::Dxt1:
				return false;
			case PixelFormat::Dxt2:
				return false;
			case PixelFormat::Dxt3:
				return false;
			case PixelFormat::Dxt4:
				return false;
			case PixelFormat::Dxt5:
				return false;
		}

		UNREACHABLE();
	}

	int PixelBuffer::GetFormatBitsPerPixel(PixelFormat format) {
		switch (format) {
			case PixelFormat::None:
				return 0x0;
			case PixelFormat::Rgba:
				return TO_BITS(sizeof(PixelFormats::Rgba));
			case PixelFormat::RgbaH:
				return TO_BITS(sizeof(PixelFormats::RgbaH));
			case PixelFormat::Rgba4444:
				return TO_BITS(sizeof(PixelFormats::Rgba4444));
			case PixelFormat::Rgba5551:
				return TO_BITS(sizeof(PixelFormats::Rgba5551));
			case PixelFormat::Rgb565:
				return TO_BITS(sizeof(PixelFormats::Rgb565));
			case PixelFormat::LuminanceAlpha:
				return TO_BITS(sizeof(PixelFormats::LuminanceAlpha));
			case PixelFormat::LuminanceAlphaH:
				return TO_BITS(sizeof(PixelFormats::LuminanceAlphaH));
			case PixelFormat::Luminance:
				return TO_BITS(sizeof(PixelFormats::Luminance));
			case PixelFormat::LuminanceH:
				return TO_BITS(sizeof(PixelFormats::LuminanceH));
			case PixelFormat::Alpha:
				return TO_BITS(sizeof(PixelFormats::Alpha));
			case PixelFormat::AlphaH:
				return TO_BITS(sizeof(PixelFormats::AlphaH));
			case PixelFormat::Depth16:
				return TO_BITS(sizeof(PixelFormats::Depth16));
			case PixelFormat::Depth24:
				return TO_BITS(sizeof(PixelFormats::Depth24));
			case PixelFormat::Depth16Stencil8:
				return TO_BITS(sizeof(PixelFormats::Depth16Stencil8));
			case PixelFormat::Depth24Stencil8:
				return TO_BITS(sizeof(PixelFormats::Depth24Stencil8));
			case PixelFormat::Dxt1:
				return Dxt1_Size;
			case PixelFormat::Dxt2:
				return Dxt2_Size;
			case PixelFormat::Dxt3:
				return Dxt3_Size;
			case PixelFormat::Dxt4:
				return Dxt4_Size;
			case PixelFormat::Dxt5:
				return Dxt5_Size;
		}
		
		UNREACHABLE();
	}

	int PixelBuffer::CalculateTotalMipMaps(int width, int height) {
		int widthMips = 1;
		int heightMips = 1;
		width /= 2;
		for (heightMips = 1; width >= 1; ++widthMips)
			width /= 2;
		for (int j = height / 2; j >= 1; ++heightMips)
			j /= 2;
		
		if (widthMips <= heightMips)
			return heightMips;

		return widthMips;
	}

	int PixelBuffer::LoadFile(const char* fileName, uint8_t* &fileData, uint32_t& fileSize) {
		if (fileName != nullptr) {
			
			// open the file
			uint64_t handle = Handles<PixelBuffer>::NoHandle;
			IoCall::PsmFileOpen((char*)fileName, SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY, &handle);
			if (handle) {
				// get the file size
				uint32_t totalFileSize = 0;
				IoCall::PsmFileGetSize(handle, &totalFileSize);

				// allocate memory for this file
				std::shared_ptr<HeapAllocator> allocator = HeapAllocator::UniqueObject();
				fileData = reinterpret_cast<uint8_t*>(allocator->sce_psm_malloc(totalFileSize));

				if (fileData != nullptr) {
					fileSize = 0;
					IoCall::PsmFileRead(handle, fileData, fileSize, &fileSize);
					return true;
				}
				else {
					IoCall::PsmClose(handle);
					return PSM_ERROR_COMMON_OUT_OF_MEMORY;
				}
			}
			else {
				return PSM_ERROR_COMMON_FILE_NOT_FOUND;
			}

		}
		else {
			return false;
		}

	}
	
	GLenum PixelBuffer::GLPixelBufferType() {
		LOG_FUNCTION();
		return this->glPixelBufferType;
	}

	GLenum PixelBuffer::GetDeviceFaceTarget(TextureCubeFace face) {
		LOG_FUNCTION();
		if (this->type == PixelBufferType::TextureCube) {
			UNIMPLEMENTED_MSG("OpenGl::GetCubeMapTarget");
		}
		else {
			return this->GLPixelBufferType();
		}
	}

	bool PixelBuffer::IsFormatDxt(PixelFormat format) {
		return (format >= PixelFormat::Dxt1);
	}

	int PixelBuffer::AdjValueForDxt(bool isDxt, int v) {
		return isDxt ? (v + 3) & ~3 : v;
	}

	int PixelBuffer::CalculateImageArraySizeInBytes(PixelFormat format, int bitsPerPixel, int width, int height)
	{
		bool isDxt = (format >= PixelFormat::Dxt1);

		int adjWidth = PixelBuffer::AdjValueForDxt(isDxt, width);
		int adjHeight = PixelBuffer::AdjValueForDxt(isDxt, height);
		int imageSize = static_cast<int>(ceil(TO_BYTES(static_cast<double>(bitsPerPixel * adjWidth))) * adjHeight);

		Logger::Debug("isDxt: 0x" + Format::Hex(isDxt));

		Logger::Debug("adjWidth: 0x" + Format::Hex(adjWidth));
		Logger::Debug("adjHeight: 0x" + Format::Hex(adjHeight));
		Logger::Debug("bpp: 0x" + Format::Hex(bitsPerPixel));

		Logger::Debug("total image size: " + Format::Hex(imageSize));

		return imageSize;
	}



}