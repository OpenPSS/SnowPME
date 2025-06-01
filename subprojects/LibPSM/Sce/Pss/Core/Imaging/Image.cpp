#include <Sce/Pss/Core/Imaging/Image.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Imaging {
	int Image::NewFromFilename(std::string filename, int* handle) {
		Unimplemented();
	}
	int Image::NewFromFileImage(uint8_t* fileImage, int* handle) {
		Unimplemented();
	}
	int Image::NewFromModeSizeColor(ImageMode mode, ImageSize* size, ImageColor* color, int* handle) {
		Unimplemented();
	}
	int Image::NewFromModeSizeBuffer(ImageMode mode, ImageSize* size, uint8_t* buffer, int* handle) {
		Unimplemented();
	}
	int Image::AddRefNative(int handle){
		Unimplemented();;
	}
	int Image::ReleaseNative(int handle){
		Unimplemented();
	}
	int Image::GetSize(int handle, ImageSize* size){
		Unimplemented();
	}
	int Image::SetDecodeSize(int handle, ImageSize* size) {
		Unimplemented();
	}
	int Image::DecodeNative(int handle) {
		Unimplemented();
	}
	int Image::GetPixelData(int handle, uint8_t* buffer, uint32_t bufferSize) {
		Unimplemented();
	}
	int Image::GetPixelDataSize(int handle, uint32_t* bufferSize) {
		Unimplemented();
	}
	int Image::ResizeNative(int handle, ImageSize* size, int* resizedImageHandle) {
		Unimplemented();
	}
	int Image::CropNative(int handle, ImageRect* rect, int* croppedImageHandle) {
		Unimplemented();
	}
	int Image::DrawImageNative(int handle, int source_handle, ImagePosition* position) {
		Unimplemented();
	}
	int Image::DrawRectangleNative(int handle, ImageColor* color, ImageRect* rect) {
		Unimplemented();
	}
	int Image::DrawTextNative(int handle, std::string text, int offset, int len, ImageColor* color, int font_handle, ImagePosition* position) {
		Unimplemented();
	}
	int Image::ExportNative(int handle, std::string albumname, std::string filename) {
		Unimplemented();
	}
	int Image::SaveAsNative(int handle, std::string filename) {
		Unimplemented();
	}
}
