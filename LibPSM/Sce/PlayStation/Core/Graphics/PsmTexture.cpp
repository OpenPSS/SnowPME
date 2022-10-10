#include "PsmTexture.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmTexture::FromFile(PixelBufferType type, MonoString* fileName, bool mipmap, PixelFormat format, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::FromImage(PixelBufferType type, std::byte* fileImage, bool mipmap, PixelFormat format, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetFilter(int handle, TextureFilter* filter) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetWrap(int handle, TextureWrap* filter) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetMaxAnisotropy(int handle, float anisotropy) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetPixels(int handle, int level, TextureCubeFace cubeFace, int* pixels, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::GenerateMipmap(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
