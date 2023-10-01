#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Bool.hpp>

using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Io;
namespace Sce::Pss::Core::Graphics {

	PixelBuffer::PixelBuffer() {
	}
	PixelBuffer::~PixelBuffer() {
	}

	int PixelBuffer::LoadFile(const char* fileName, uint8_t* &fileData, uint32_t& fileSize) {
		if (fileName != nullptr) {
			// open the file
			uint64_t psmHandle = NULL;
			ICall::PsmFileOpen((char*)fileName, SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY, &psmHandle);
			if (psmHandle) {
				// get the file size
				uint32_t totalFileSize = NULL;
				ICall::PsmFileGetSize(psmHandle, &totalFileSize);

				// allocate memory for this file
				HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();
				fileData = allocator->sce_psm_malloc(totalFileSize);

				if (fileData != nullptr) {
					fileSize = NULL;
					ICall::PsmFileRead(psmHandle, fileData, fileSize, &fileSize);
					return PSM_TRUE;
				}
				else {
					ICall::PsmClose(psmHandle);
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