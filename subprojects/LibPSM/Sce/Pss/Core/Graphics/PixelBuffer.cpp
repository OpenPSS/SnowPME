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



}