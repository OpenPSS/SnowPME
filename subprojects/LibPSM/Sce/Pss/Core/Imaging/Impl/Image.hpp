#ifndef LIB_PSS_IMPL_IMAGE_H
#define LIB_PSS_IMPL_IMAGE_H 1
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Imaging::Impl {

	class Image : public Errorable{
	private:
		uint8_t* image = nullptr;
		int x = 0;
		int y = 0;
		int comp = 0;
	public:
		int Open(const uint8_t* data, uint32_t dataLen, Sce::Pss::Core::Memory::HeapAllocator* alloc);
		Image();
		virtual ~Image();
	};
}
#endif