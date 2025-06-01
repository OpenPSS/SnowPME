#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Imaging/Impl/Image.hpp>

#include <glad/glad.h>
#include <LibShared.hpp>
#include <string.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Imaging;

namespace Sce::Pss::Core::Graphics {


	Texture2D::Texture2D(std::string* fileName, bool mipmap, PixelFormat format) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD();

		if (fileName != nullptr) {
			this->Filename = std::string(fileName->c_str(), strlen(fileName->c_str()));

			uint8_t* fileData = nullptr;
			uint32_t fileSize = 0;

			// load the file data
			if (this->LoadFile(this->Filename.c_str(), fileData, fileSize)) {

				// parse image file 
				this->LoadImage(fileData, fileSize, mipmap, format);

				// free the file data
				HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();
				allocator->sce_psm_free(fileData);
			}
		}
		else {
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_NULL);
		}
	}

	int Texture2D::LoadImage(uint8_t* data, uint32_t dataLen, bool mipmap, PixelFormat format) {
		Logger::Debug(__FUNCTION__);

		int err;
		HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();

		err = this->image.Open(data, dataLen, allocator);
		if (err != PSM_ERROR_NO_ERROR) {
			return err;
		}

		UNIMPLEMENTED();
	}

	Texture2D::~Texture2D() {
		Logger::Debug(__FUNCTION__);
	}

	GLenum Texture2D::GlTextureType() {
		Logger::Debug(__FUNCTION__);
		return GL_TEXTURE_2D;
	}

	int Texture2D::ActiveStateChanged(bool state) {
		Logger::Debug(__FUNCTION__);
		return PSM_ERROR_NO_ERROR;
	}

}
