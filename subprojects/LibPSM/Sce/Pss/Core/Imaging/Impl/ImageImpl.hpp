#ifndef LIB_PSS_IMPL_IMAGE_H
#define LIB_PSS_IMPL_IMAGE_H 1
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Imaging/ImageSize.hpp>
#include <Sce/Pss/Core/Imaging/Impl/ImageImplMode.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Imaging::Impl {

	class ImageImpl : public Errorable {
	private:
		int channels = 0;
		std::weak_ptr<Sce::Pss::Core::Memory::HeapAllocator> allocator;
		ImageImplMode mode;
		ImageSize imgSize = { 0,0 };

	public:
		static std::shared_ptr<ImageImpl> Open(const uint8_t* data, uint32_t dataLen, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc);
		static std::shared_ptr<ImageImpl> CreateFromBuffer(uint8_t* imageBuffer, ImageSize* size, ImageImplMode mode, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc);

		ImageImplMode GetMode();
		int ConvertMode();
		int GetExtent(ImageSize* extent);
		int ToBuffer(void* pngBuffer, int unk0);

		uint8_t* ImgBuffer = nullptr;

		ImageImpl(ImageImplMode mode);
		virtual ~ImageImpl();
	};
}
#endif