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
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Imaging/Impl/ImageImpl.hpp>
#include <Sce/Pss/Core/Features.hpp>
#include <mono/mono.h>
#include <memory>

namespace Sce::Pss::Core::Imaging {
	class Image : public PsmObject<Image> {
	private:
		std::shared_ptr<Sce::Pss::Core::Imaging::Impl::ImageImpl> imageImpl = nullptr;
		void normalizeColor(ImageColor* color);
	public:
		int Decode();
		int DrawRectangle(ImageColor color, ImageRect rect);
		ImageSize Size();
		Image(ImageMode mode, ImageSize* size, ImageColor* color);
		~Image() = default;

		static int NewFromFilename(MonoString* filename, int* handle);
		static int NewFromFileImage(MonoArray* fileImage, int* handle);
		static int NewFromModeSizeColor(ImageMode mode, ImageSize* size, ImageColor* color, int* handle);
		static int NewFromModeSizeBuffer(ImageMode mode, ImageSize* size, MonoArray* buffer, int* handle);
		static int AddRefNative(int handle);
		static int ReleaseNative(int handle);
		static int GetSize(int handle, ImageSize* size);
		static int SetDecodeSize(int handle, ImageSize* size);
		static int DecodeNative(int handle);
		static int GetPixelData(int handle, uint8_t *buffer, uint32_t bufferSize);
		static int GetPixelDataSize(int handle, uint32_t *bufferSize);
		static int ResizeNative(int handle, ImageSize* size, int *resizedImageHandle);
		static int CropNative(int handle, ImageRect* rect, int *croppedImageHandle);
		static int DrawImageNative(int handle, int source_handle, ImagePosition *position);
		static int DrawRectangleNative(int handle, ImageColor *color, ImageRect *rect);

		// NOTE: on SDK2.00 Windows; these are int offset and int len, its only uint on PSVita.
#ifdef COMPAT_VITA_2_01_RUNTIME_FEATURES
		static int DrawTextNative(int handle, MonoString* text, uint32_t offset, uint32_t len, ImageColor* color, int font_handle, ImagePosition* position);
#else
		static int DrawTextNative(int handle, MonoString* text, int offset, int len, ImageColor* color, int font_handle, ImagePosition* position);
#endif
		static int ExportNative(int handle, MonoString* albumname, MonoString* filename);
		static int SaveAsNative(int handle, MonoString* filename);
	};
}
#endif
