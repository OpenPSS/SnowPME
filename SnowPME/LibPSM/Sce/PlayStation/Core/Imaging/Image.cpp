#include "Image.hpp"

namespace Sce::PlayStation::Core::Imaging {
	int Image::NewFromFilename(string filename, int* handle) {
		cout << "Sce::PlayStation::Core::Imaging::NewFromFilename(string, int *) Unimplemented." << endl;
		return 0;
	}
	int Image::NewFromFileImage(byte* fileImage, int* handle) {
		cout << "Sce::PlayStation::Core::Imaging::NewFromFileImage(byte*, int *) Unimplemented." << endl;
		return 0;
	}
	int Image::NewFromModeSizeColor(ImageMode mode, ImageSize* size, ImageColor* color, int* handle) {
		cout << "Sce::PlayStation::Core::Imaging::NewFromModeSizeColor(Sce::PlayStation::Core::Imaging::ImageMode, Sce::PlayStation::Core::Imaging::ImageSize *, Sce::PlayStation::Core::Imaging::ImageColor *, int *) Unimplemented." << endl;
		return 0;
	}
	int Image::NewFromModeSizeBuffer(ImageMode mode, ImageSize* size, byte* buffer, int* handle) {
		cout << "Sce::PlayStation::Core::Imaging::NewFromModeSizeBuffer(Sce::PlayStation::Core::Imaging::ImageMode, Sce::PlayStation::Core::Imaging::ImageSize *, byte*, int *) Unimplemented." << endl;
		return 0;
	}
	int Image::AddRefNative(int handle){
		cout << "Sce::PlayStation::Core::Imaging::AddRefNative(int) Unimplemented." << endl;
		return 0;
	}
	int Image::ReleaseNative(int handle){
		cout << "Sce::PlayStation::Core::Imaging::ReleaseNative(int) Unimplemented." << endl;
		return 0;
	}
	int Image::GetSize(int handle, ImageSize* size){
		cout << "Sce::PlayStation::Core::Imaging::GetSize(int, Sce::PlayStation::Core::Imaging::ImageSize *) Unimplemented." << endl;
		return 0;
	}
	int Image::SetDecodeSize(int handle, ImageSize* size) {
		cout << "Sce::PlayStation::Core::Imaging::SetDecodeSize(int, Sce::PlayStation::Core::Imaging::ImageSize *) Unimplemented." << endl;
		return 0;
	}
	int Image::DecodeNative(int handle) {
		cout << "Sce::PlayStation::Core::Imaging::DecodeNative(int) Unimplemented." << endl;
		return 0;
	}
	int Image::GetPixelData(int handle, byte* buffer, uint32_t bufferSize) {
		cout << "Sce::PlayStation::Core::Imaging::GetPixelData(int, byte*, uint32_t) Unimplemented." << endl;
		return 0;
	}
	int Image::GetPixelDataSize(int handle, uint32_t* bufferSize) {
		cout << "Sce::PlayStation::Core::Imaging::GetPixelDataSize(int, uint32_t *) Unimplemented." << endl;
		return 0;
	}
	int Image::ResizeNative(int handle, ImageSize* size, int* resizedImageHandle) {
		cout << "Sce::PlayStation::Core::Imaging::ResizeNative(int, Sce::PlayStation::Core::Imaging::ImageSize *, int *) Unimplemented." << endl;
		return 0;
	}
	int Image::CropNative(int handle, ImageRect* rect, int* croppedImageHandle) {
		cout << "Sce::PlayStation::Core::Imaging::CropNative(int, Sce::PlayStation::Core::Imaging::ImageRect *, int *) Unimplemented." << endl;
		return 0;
	}
	int Image::DrawImageNative(int handle, int source_handle, ImagePosition* position) {
		cout << "Sce::PlayStation::Core::Imaging::DrawImageNative(int, int, Sce::PlayStation::Core::Imaging::ImagePosition *) Unimplemented." << endl;
		return 0;
	}
	int Image::DrawRectangleNative(int handle, ImageColor* color, ImageRect* rect) {
		cout << "Sce::PlayStation::Core::Imaging::DrawRectangleNative(int, Sce::PlayStation::Core::Imaging::ImageColor *, Sce::PlayStation::Core::Imaging::ImageRect *) Unimplemented." << endl;
		return 0;
	}
	int Image::DrawTextNative(int handle, string text, int offset, int len, ImageColor* color, int font_handle, ImagePosition* position) {
		cout << "Sce::PlayStation::Core::Imaging::DrawTextNative(int, string, int, int, Sce::PlayStation::Core::Imaging::ImageColor *, int, Sce::PlayStation::Core::Imaging::ImagePosition *) Unimplemented." << endl;
		return 0;
	}
	int Image::ExportNative(int handle, string albumname, string filename) {
		cout << "Sce::PlayStation::Core::Imaging::ExportNative(int, string, string) Unimplemented." << endl;
		return 0;
	}
	int Image::SaveAsNative(int handle, string filename) {
		cout << "Sce::PlayStation::Core::Imaging::SaveAsNative(int, string) Unimplemented." << endl;
		return 0;
	}
}
