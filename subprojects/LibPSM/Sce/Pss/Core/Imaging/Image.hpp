#ifndef LIB_PSS_IMAGE_H
#define LIB_PSS_IMAGE_H 1

#include <string>
#include <iostream>
#include <cstdint>
#include <Sce/Pss/Core/Imaging/ImageSize.hpp>
#include <Sce/Pss/Core/Imaging/ImageColor.hpp>
#include <Sce/Pss/Core/Imaging/ImageRect.hpp>
#include <Sce/Pss/Core/Imaging/ImagePosition.hpp>
#include <Sce/Pss/Core/Imaging/ImageMode.hpp>

namespace Sce::Pss::Core::Imaging {
	class Image {
	public:
		static int NewFromFilename(std::string filename, int *handle);
		static int NewFromFileImage(uint8_t *fileImage, int * handle);
		static int NewFromModeSizeColor(ImageMode mode, ImageSize *size, ImageColor *color, int *handle);
		static int NewFromModeSizeBuffer(ImageMode mode, ImageSize *size, uint8_t *buffer, int *handle);
		static int AddRefNative(int handle);
		static int ReleaseNative(int handle);
		static int GetSize(int handle, ImageSize *size);
		static int SetDecodeSize(int handle, ImageSize *size);
		static int DecodeNative(int handle);
		static int GetPixelData(int handle, uint8_t *buffer, uint32_t bufferSize);
		static int GetPixelDataSize(int handle, uint32_t *bufferSize);
		static int ResizeNative(int handle, ImageSize *size, int *resizedImageHandle);
		static int CropNative(int handle, ImageRect *rect, int *croppedImageHandle);
		static int DrawImageNative(int handle, int source_handle, ImagePosition *position);
		static int DrawRectangleNative(int handle, ImageColor *color, ImageRect *rect);
		static int DrawTextNative(int handle, std::string text, int offset, int len, ImageColor *color, int font_handle, ImagePosition *position);
		static int ExportNative(int handle, std::string albumname, std::string filename);
		static int SaveAsNative(int handle, std::string filename);
	};
}
#endif
