#include "PsmTexture.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmTexture::FromFile(PixelBufferType type, std::string fileName, bool mipmap, PixelFormat format, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::FromFile(Sce::PlayStation::Core::Graphics::PixelBufferType, string, bool, Sce::PlayStation::Core::Graphics::PixelFormat, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmTexture::FromImage(PixelBufferType type, std::byte* fileImage, bool mipmap, PixelFormat format, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::FromImage(Sce::PlayStation::Core::Graphics::PixelBufferType, byte*, bool, Sce::PlayStation::Core::Graphics::PixelFormat, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmTexture::SetFilter(int handle, TextureFilter* filter) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetFilter(int, Sce::PlayStation::Core::Graphics::TextureFilter *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmTexture::SetWrap(int handle, TextureWrap* filter) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetWrap(int, Sce::PlayStation::Core::Graphics::TextureWrap *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmTexture::SetMaxAnisotropy(int handle, float anisotropy) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetMaxAnisotropy(int, float) Unimplemented." << std::endl;
		return 0;
	}
	int PsmTexture::SetPixels(int handle, int level, TextureCubeFace cubeFace, int* pixels, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetPixels(int, int, Sce::PlayStation::Core::Graphics::TextureCubeFace, System::Array, Sce::PlayStation::Core::Graphics::PixelFormat, int, int, int, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmTexture::GenerateMipmap(int handle) {
		std::cout << "Sce::PlayStation::Core::Graphics::GenerateMipmap(int) Unimplemented." << std::endl;
		return 0;
	}
}
