#ifndef LIB_PSM_IMAGE_H
#define LIB_PSM_IMAGE_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "ImageSize.hpp"
#include "ImageColor.hpp"
#include "ImageRect.hpp"
#include "ImagePosition.hpp"
#include "ImageMode.hpp"

using namespace std;

namespace Sce::PlayStation::Core::Imaging {
	class Image {
	public:
		static int NewFromFilename(string filename, int *handle);
		static int NewFromFileImage(byte *fileImage, int * handle);
		static int NewFromModeSizeColor(ImageMode mode, ImageSize *size, ImageColor *color, int *handle);
		static int NewFromModeSizeBuffer(ImageMode mode, ImageSize *size, byte *buffer, int *handle);
		static int AddRefNative(int handle);
		static int ReleaseNative(int handle);
		static int GetSize(int handle, ImageSize *size);
		static int SetDecodeSize(int handle, ImageSize *size);
		static int DecodeNative(int handle);
		static int GetPixelData(int handle, byte *buffer, uint32_t bufferSize);
		static int GetPixelDataSize(int handle, uint32_t *bufferSize);
		static int ResizeNative(int handle, ImageSize *size, int *resizedImageHandle);
		static int CropNative(int handle, ImageRect *rect, int *croppedImageHandle);
		static int DrawImageNative(int handle, int source_handle, ImagePosition *position);
		static int DrawRectangleNative(int handle, ImageColor *color, ImageRect *rect);
		static int DrawTextNative(int handle, string text, int offset, int len, ImageColor *color, int font_handle, ImagePosition *position);
		static int ExportNative(int handle, string albumname, string filename);
		static int SaveAsNative(int handle, string filename);
	};
}
#endif
