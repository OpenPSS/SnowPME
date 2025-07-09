#ifndef LIB_PSS_IMPL_IMAGE_H
#define LIB_PSS_IMPL_IMAGE_H 1
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Imaging/ImageSize.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Imaging::Impl {

	class ImageImpl : public Errorable {
	private:
		uint8_t* imageBuffer = nullptr;
		ImageSize imageSize = { 0,0 };
		int channels = 0;
		std::weak_ptr<Sce::Pss::Core::Memory::HeapAllocator> allocator;

	public:
		static std::shared_ptr<ImageImpl> Open(const uint8_t* data, uint32_t dataLen, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc);

		// in psm.exe : 
		// 		std::shared_ptr<ImageImpl> CreateFromBuffer(int* unk0, uint8_t* imageBuffer, int unk1, int unk2, int unk3, ImageSize* size, int unk4, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc);

		static std::shared_ptr<ImageImpl> CreateFromBuffer(uint8_t* imageBuffer, ImageSize* size, int channels, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc);

		int GetMode();
		int ConvertMode();
		int GetExtent(int* extent);
		int ToBuffer(void* pngBuffer, int unk0);

		ImageImpl();
		virtual ~ImageImpl();
	};
}
#endif