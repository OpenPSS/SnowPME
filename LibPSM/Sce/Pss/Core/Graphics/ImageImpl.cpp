#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Sce/Pss/Core/Graphics/ImageImpl.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <LibShared.hpp>

using namespace Sce::Pss::Core::Memory;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	ImageImpl::ImageImpl() {
		image = nullptr;
	}

	ImageImpl::~ImageImpl() {
		if (image != nullptr) {
			stbi_image_free(image);
		}
	}

	int ImageImpl::Open(const uint8_t* data, uint32_t dataLen, Sce::Pss::Core::Memory::HeapAllocator* alloc) {
		Logger::Debug(__FUNCTION__);

		(void)alloc;
		// TODO: Use allocator!
		image = stbi_load_from_memory(data, dataLen, &x, &y, &comp, 4);
		return image ? PSM_ERROR_NO_ERROR : PSM_ERROR_COMMON_INVALID_FORMAT;
	}

}