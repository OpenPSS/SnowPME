#include "Image.hpp"

namespace Sce::Pss::Core::Imaging {
	int Image::NewFromFilename(std::string filename, int* handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::NewFromFileImage(uint8_t* fileImage, int* handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::NewFromModeSizeColor(ImageMode mode, ImageSize* size, ImageColor* color, int* handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::NewFromModeSizeBuffer(ImageMode mode, ImageSize* size, uint8_t* buffer, int* handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::AddRefNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::ReleaseNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::GetSize(int handle, ImageSize* size){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::SetDecodeSize(int handle, ImageSize* size) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::DecodeNative(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::GetPixelData(int handle, uint8_t* buffer, uint32_t bufferSize) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::GetPixelDataSize(int handle, uint32_t* bufferSize) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::ResizeNative(int handle, ImageSize* size, int* resizedImageHandle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::CropNative(int handle, ImageRect* rect, int* croppedImageHandle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::DrawImageNative(int handle, int source_handle, ImagePosition* position) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::DrawRectangleNative(int handle, ImageColor* color, ImageRect* rect) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::DrawTextNative(int handle, std::string text, int offset, int len, ImageColor* color, int font_handle, ImagePosition* position) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::ExportNative(int handle, std::string albumname, std::string filename) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Image::SaveAsNative(int handle, std::string filename) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
