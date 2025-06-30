#ifndef LIB_PSS_IMPL_IMAGE_H
#define LIB_PSS_IMPL_IMAGE_H 1
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Imaging::Impl {

	class Image : public Errorable {
	private:
		uint8_t* image = nullptr;
		int x = 0;
		int y = 0;
		int comp = 0;
	public:
		int Open(const uint8_t* data, uint32_t dataLen, std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc);
		int GetMode();
		int ConvertMode();
		int GetExtent(int* extent);
		int ToBuffer(void* pngBuffer, int unk0);
		Image();
		virtual ~Image();
	};
}
#endif