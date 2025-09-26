#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Imaging/Impl/ImageImpl.hpp>
#include <Sce/Pss/Core/Imaging/ImageSize.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>

using namespace Sce::Pss::Core::Memory;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Imaging::Impl {

	ImageImpl::ImageImpl(ImageImplMode mode) {
		this->imgSize.Width = 0;
		this->imgSize.Height = 0;
		this->mode = mode;
	}

	ImageImpl::~ImageImpl() {
		if (this->ImgBuffer != nullptr) {
			this->allocator.lock()->sce_psm_free(ImgBuffer);
		}
	}

	ImageImplMode ImageImpl::GetMode() {
		return this->mode;
	}
	
	int ImageImpl::ConvertMode() {
		UNIMPLEMENTED();
	}
	

	int ImageImpl::GetExtent(ImageSize* extent) {
		if (extent != nullptr) {
			*extent = this->imgSize;
		}
		return PSM_ERROR_NO_ERROR;
	}

	int ImageImpl::ToBuffer(void* pngBuffer, int unk0) {
		UNIMPLEMENTED();
	}

	std::shared_ptr<ImageImpl> ImageImpl::CreateFromBuffer(uint8_t* imageBuffer, ImageSize* size, ImageImplMode mode, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc) {
		std::shared_ptr<ImageImpl> implImg = std::make_shared<ImageImpl>(mode);

		implImg->allocator = alloc;
		implImg->imgSize = *size;
		implImg->channels = (mode == ImageImplMode::Rgba ? sizeof(uint32_t) : sizeof(uint8_t));

		implImg->ImgBufferSize = size->Width * size->Height * implImg->channels;
		implImg->ImgBuffer = reinterpret_cast<uint8_t*>(alloc->sce_psm_malloc(implImg->ImgBufferSize));

		if (implImg->ImgBuffer != nullptr) {
			memcpy(implImg->ImgBuffer, imageBuffer, implImg->ImgBufferSize);
		}

		return implImg;
	}

	std::shared_ptr<ImageImpl> ImageImpl::Open(const uint8_t* data, uint32_t dataLen, std::shared_ptr<HeapAllocator> alloc) {
		std::shared_ptr<ImageImpl> implImg = std::make_shared<ImageImpl>(ImageImplMode::Rgba);

		implImg->allocator = alloc;

		if (memcmp("MIG", data, 3) == 0) {
			PANIC("Implement .GIM parsing to the image library (how did you even trigger this?)");
		}

		stbi_uc* stbImg = stbi_load_from_memory(data, dataLen, &implImg->imgSize.Width, &implImg->imgSize.Height, &implImg->channels, 4);

		implImg->ImgBufferSize = implImg->imgSize.Width * implImg->imgSize.Height * implImg->channels;
		implImg->ImgBuffer = reinterpret_cast<uint8_t*>(alloc->sce_psm_malloc(implImg->ImgBufferSize));

		if (implImg->ImgBuffer != nullptr) {
			memcpy(implImg->ImgBuffer, stbImg, implImg->ImgBufferSize);
		}

		stbi_image_free(stbImg);

		return implImg;
	}

}