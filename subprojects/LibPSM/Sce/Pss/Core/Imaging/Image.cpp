#include <Sce/Pss/Core/Imaging/Image.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Imaging {
	int Image::NewFromFilename(std::string filename, int* handle) {
		UNIMPLEMENTED();
	}
	int Image::NewFromFileImage(uint8_t* fileImage, int* handle) {
		UNIMPLEMENTED();
	}
	int Image::NewFromModeSizeColor(ImageMode mode, ImageSize* size, ImageColor* color, int* handle) {
		UNIMPLEMENTED();
	}
	int Image::NewFromModeSizeBuffer(ImageMode mode, ImageSize* size, uint8_t* buffer, int* handle) {
		UNIMPLEMENTED();
	}
	int Image::AddRefNative(int handle){
		UNIMPLEMENTED();;
	}
	int Image::ReleaseNative(int handle){
		UNIMPLEMENTED();
	}
	int Image::GetSize(int handle, ImageSize* size){
		UNIMPLEMENTED();
	}
	int Image::SetDecodeSize(int handle, ImageSize* size) {
		UNIMPLEMENTED();
	}
	int Image::DecodeNative(int handle) {
		UNIMPLEMENTED();
	}
	int Image::GetPixelData(int handle, uint8_t* buffer, uint32_t bufferSize) {
		UNIMPLEMENTED();
	}
	int Image::GetPixelDataSize(int handle, uint32_t* bufferSize) {
		UNIMPLEMENTED();
	}
	int Image::ResizeNative(int handle, ImageSize* size, int* resizedImageHandle) {
		UNIMPLEMENTED();
	}
	int Image::CropNative(int handle, ImageRect* rect, int* croppedImageHandle) {
		UNIMPLEMENTED();
	}
	int Image::DrawImageNative(int handle, int source_handle, ImagePosition* position) {
		UNIMPLEMENTED();
	}
	int Image::DrawRectangleNative(int handle, ImageColor* color, ImageRect* rect) {
		UNIMPLEMENTED();
	}
	int Image::DrawTextNative(int handle, std::string text, int offset, int len, ImageColor* color, int font_handle, ImagePosition* position) {
		UNIMPLEMENTED();
	}
	int Image::ExportNative(int handle, std::string albumname, std::string filename) {
		UNIMPLEMENTED();
	}
	int Image::SaveAsNative(int handle, std::string filename) {
		UNIMPLEMENTED();
	}
}
