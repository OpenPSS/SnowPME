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

	ImageImpl::ImageImpl() {
		this->imageSize.Width = 0;
		this->imageSize.Height = 0;
	}

	ImageImpl::~ImageImpl() {
		if (imageBuffer != nullptr) {
			this->allocator.lock()->sce_psm_free(imageBuffer);
		}
	}

	int GetMode() {
		UNIMPLEMENTED();
	}
	
	int ConvertMode() {
		UNIMPLEMENTED();
	}
	
	int GetExtent(int* extent) {
		UNIMPLEMENTED();
	}

	int ToBuffer(void* pngBuffer, int unk0) {
		UNIMPLEMENTED();
	}

	std::shared_ptr<ImageImpl> ImageImpl::CreateFromBuffer(uint8_t* imageBuffer, ImageSize* size, int channels, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc) {
		std::shared_ptr<ImageImpl> implImg = std::make_shared<ImageImpl>();

		implImg->allocator = alloc;

		implImg->imageSize = *size;
		implImg->channels = channels;

		int imgSize = size->Width * size->Height * channels;
		implImg->imageBuffer = reinterpret_cast<uint8_t*>(alloc->sce_psm_malloc(imgSize));

		if (implImg->imageBuffer != nullptr) {
			memcpy(implImg->imageBuffer, imageBuffer, imgSize);
		}

		return implImg;
	}

	std::shared_ptr<ImageImpl> ImageImpl::Open(const uint8_t* data, uint32_t dataLen, std::shared_ptr<HeapAllocator> alloc) {
		std::shared_ptr<ImageImpl> implImg = std::make_shared<ImageImpl>();

		implImg->allocator = alloc;

		if (memcmp("MIG", data, 3) == 0) {
			PANIC("Implement .GIM parsing to the image library (how did you even trigger this?)");
		}

		stbi_uc* stbImg = stbi_load_from_memory(data, dataLen, &implImg->imageSize.Width, &implImg->imageSize.Height, &implImg->channels, 4);

		int totalSz = implImg->imageSize.Width * implImg->imageSize.Height * implImg->channels;
		implImg->imageBuffer = reinterpret_cast<uint8_t*>(alloc->sce_psm_malloc(totalSz));

		if (implImg->imageBuffer != nullptr) {
			memcpy(implImg->imageBuffer, stbImg, totalSz);
		}

		stbi_image_free(stbImg);

		return implImg;
	}

}