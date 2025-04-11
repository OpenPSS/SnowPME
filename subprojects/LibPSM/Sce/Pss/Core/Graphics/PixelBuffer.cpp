#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Bool.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>

#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferType.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferOption.hpp>


namespace Sce::Pss::Core::Graphics {
	using namespace Sce::Pss::Core::System;
	using namespace Sce::Pss::Core::Memory;
	using namespace Sce::Pss::Core::Io;

	PixelBuffer::PixelBuffer() {
	}
	PixelBuffer::~PixelBuffer() {
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

	int PixelBuffer::LoadFile(const char* fileName, uint8_t* &fileData, uint32_t& fileSize) {
		if (fileName != nullptr) {
			// open the file
			uint64_t handle = Handles::NoHandle;
			ICall::PsmFileOpen((char*)fileName, SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY, &handle);
			if (handle) {
				// get the file size
				uint32_t totalFileSize = NULL;
				ICall::PsmFileGetSize(handle, &totalFileSize);

				// allocate memory for this file
				HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();
				fileData = allocator->sce_psm_malloc(totalFileSize);

				if (fileData != nullptr) {
					fileSize = NULL;
					ICall::PsmFileRead(handle, fileData, fileSize, &fileSize);
					return PSM_TRUE;
				}
				else {
					ICall::PsmClose(handle);
					return this->SetError(PSM_ERROR_COMMON_OUT_OF_MEMORY);
				}
			}
			else {
				return this->SetError(PSM_ERROR_COMMON_FILE_NOT_FOUND);
			}

		}
		else {
			return PSM_FALSE;
		}


	}

}