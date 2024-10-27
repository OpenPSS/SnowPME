#pragma once

#include <Sce/Pss/Core/Graphics/ImageImpl.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>

#include <cstdint>

namespace Sce::Pss::Core::Graphics {

	class ImageImpl {
	public:
		int Open(const uint8_t* data, uint32_t dataLen, Sce::Pss::Core::Memory::HeapAllocator* alloc);

		ImageImpl();
		virtual ~ImageImpl();

	private:
		uint8_t* image = nullptr;
		int x = NULL;
		int y = NULL;
		int comp = NULL;
	};
}