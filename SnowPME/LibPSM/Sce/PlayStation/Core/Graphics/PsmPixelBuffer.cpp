#include "PsmPixelBuffer.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmPixelBuffer::Create(PixelBufferType type, int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption option2, int* result) {
		cout << "Sce::PlayStation::Core::Graphics::Create(Sce::PlayStation::Core::Graphics::PixelBufferType, int, int, bool, Sce::PlayStation::Core::Graphics::PixelFormat, Sce::PlayStation::Core::Graphics::PixelBufferOption, Sce::PlayStation::Core::Graphics::InternalOption, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmPixelBuffer::Delete(int handle) {
		cout << "Sce::PlayStation::Core::Graphics::Delete(int) Unimplemented." << endl;
		return 0;
	}
	int PsmPixelBuffer::AddRef(int handle) {
		cout << "Sce::PlayStation::Core::Graphics::AddRef(int) Unimplemented." << endl;
		return 0;
	}
	int PsmPixelBuffer::GetInfo(int handle, PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option){
		cout << "Sce::PlayStation::Core::Graphics::GetInfo(int, Sce::PlayStation::Core::Graphics::PixelBufferType *, int *, int *, int *, Sce::PlayStation::Core::Graphics::PixelFormat *, Sce::PlayStation::Core::Graphics::PixelBufferOption *) Unimplemented." << endl;
		return 0;
	}
}
