#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Bool.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>

#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferType.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferOption.hpp>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Io;

namespace Sce::Pss::Core::Graphics {

	// WTF?
	uint8_t PixelBuffer::formatProperties[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x20, 0x18, 0x8, 0x0,0x0, 0x0, 0x0, 0x40, 0x40, 0x30,
												0x10, 0x0, 0x0, 0x0, 0x40, 0x10, 0x10, 0x0C, 0x4, 0x0, 0x0, 0x0, 0x0, 0x10,
												0x10, 0x0F, 0x1, 0x0, 0x0, 0x0, 0x0, 0x10, 0x10, 0x10, 0x0, 0x0, 0x0, 0x0,
												0x0, 0x10, 0x10, 0x0, 0x8, 0x8, 0x0, 0x0, 0x0, 0x20, 0x20, 0x0, 0x10, 0x10,
												0x0, 0x0, 0x20, 0x8, 0x8, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x10, 0x10, 0x0, 0x0, 0x10,
												0x0, 0x0, 0x10, 0x8, 0x8, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x10, 0x10, 0x0, 0x10,
												0x0, 0x0, 0x0, 0x10, 0x10, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x20, 0x0, 0x0,
												0x0, 0x0, 0x18, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x10, 0x8, 0x0, 0x20, 0x0,
												0x0, 0x0, 0x0, 0x18, 0x8, 0x0, 0x4, 0x4, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x8, 0x4,
												0x4, 0x0, 0x0, 0x0, 0x0, 0x8, 0x8, 0x4, 0x4, 0x0, 0x0, 0x0, 0x0, 0x8, 0x8, 0x4, 0x4, 0x0,
												0x0, 0x0, 0x0, 0x8, 0x8, 0x4, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
												0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
												0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
												0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
												0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
												0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

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
		*level = this->level;
		*format = this->format;
		*option = this->option;
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
		if (format < PixelFormat::Dxt1 || ((width - 1) & width) == 0 && ((height - 1) & height) == 0)
			return true;
		ExceptionInfo::AddMessage("Unsupported size for compressed texture\n");
		return PixelBuffer::SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
	}

	int PixelBuffer::GetFormatHasDepth(PixelFormat format) {
		return PixelBuffer::formatProperties[(8 * (format & 0x1F)) + 3];
	}

	int PixelBuffer::GetFormatHasRgb(PixelFormat format) {
		return PixelBuffer::formatProperties[8 * (format & 0x1F)];
	}

	int PixelBuffer::GetFormatHasHalfFloat(PixelFormat format) {
		return PixelBuffer::formatProperties[8 * (format & 0x1F) + 5];
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



}