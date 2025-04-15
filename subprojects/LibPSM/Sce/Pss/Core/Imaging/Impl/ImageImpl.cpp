#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Imaging/Impl/Image.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <LibShared.hpp>

using namespace Sce::Pss::Core::Memory;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Imaging::Impl {

	Image::Image() {
		this->image = nullptr;
	}

	Image::~Image() {
		if (image != nullptr) {
			stbi_image_free(image);
		}
	}

	int Image::Open(const uint8_t* data, uint32_t dataLen, HeapAllocator* alloc) {

		(void)alloc;
		// TODO: Use allocator!


		this->image = stbi_load_from_memory(data, dataLen, &this->x, &this->y, &this->comp, 4);
		return this->image ? PSM_ERROR_NO_ERROR : PSM_ERROR_COMMON_INVALID_FORMAT;
	}

}