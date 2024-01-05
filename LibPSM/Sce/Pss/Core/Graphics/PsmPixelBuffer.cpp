#include "PsmPixelBuffer.hpp"

namespace Sce::Pss::Core::Graphics {
	int PsmPixelBuffer::Create(PixelBufferType type, int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption option2, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmPixelBuffer::Delete(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmPixelBuffer::AddRef(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmPixelBuffer::GetInfo(int handle, PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
