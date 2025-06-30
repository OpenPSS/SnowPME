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

	Texture2D::Texture2D(std::string& fileName, bool mipmap, PixelFormat format) {
		LOG_FUNCTION();
		LOCK_GUARD();

		if (!fileName.empty()) {
			this->Filename = std::string(fileName.c_str(), strlen(fileName.c_str()));

			uint8_t* fileData = nullptr;
			uint32_t fileSize = 0;

			// load the file data
			int res = this->LoadFile(this->Filename.c_str(), fileData, fileSize);
			if (res == PSM_ERROR_NO_ERROR) {

				// parse image file 
				this->LoadImage(fileData, fileSize, mipmap, format);

				// free the file data
				std::shared_ptr<HeapAllocator> allocator = HeapAllocator::UniqueObject();
				allocator->sce_psm_free(fileData);
			}
			else {
				this->SetError(res);
			}
		}
		else {
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_NULL);
		}
	}

	int Texture2D::LoadImage(uint8_t* data, uint32_t dataLen, bool mipmap, PixelFormat format) {
		LOG_FUNCTION();

		int err;
		std::shared_ptr<HeapAllocator> allocator = HeapAllocator::UniqueObject();

		err = this->image.Open(data, dataLen, allocator);
		if (err != PSM_ERROR_NO_ERROR) {
			return err;
		}

		UNIMPLEMENTED();
	}

	int Texture2D::InitImage() {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

	Texture2D::~Texture2D() {
		LOG_FUNCTION();
	}

	GLenum Texture2D::GLTextureType() {
		LOG_FUNCTION();
		return GL_TEXTURE_2D;
	}

	int Texture2D::ActiveStateChanged(bool state) {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

}
