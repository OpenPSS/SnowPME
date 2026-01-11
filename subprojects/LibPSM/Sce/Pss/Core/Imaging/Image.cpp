#include <Sce/Pss/Core/Imaging/Image.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Imaging/Impl/ImageImplMode.hpp>
#include <Sce/Pss/Core/Features.hpp>
#include <Sce/Pss/Core/Imaging/PixelData.hpp>
#include <LibShared.hpp>
#include <mono/mono.h>

#include <cstdint>
#include <string>
#include <cstdio>

using namespace Shared;
using namespace Shared::String;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Imaging::Impl;

namespace Sce::Pss::Core::Imaging {

	inline void Image::normalizeColor(ImageColor* color) {
		
		if (color->R >= 255) color->R = 255;
		else color->R = (color->R < 0 ? 0 : color->R);

		if (color->G >= 255) color->G = 255;
		else color->G = (color->G < 0 ? 0 : color->G);

		if (color->B >= 255) color->B = 255;
		else color->B = (color->B < 0 ? 0 : color->B);

		if (color->A >= 255) color->A = 255;
		else color->A = (color->A < 0 ? 0 : color->A);

	}

	ImageSize Image::Size() {
		ImageSize size;
		if (this->imageImpl != nullptr) {
			this->imageImpl->GetExtent(&size);
		}
		else {
			size.Width = 0;
			size.Height = 0;
		}
		return size;
	}

	int Image::Decode() {
		ImageSize extent;
		void* pngBuffer = nullptr;
		
		// get image size ..
		this->imageImpl->GetExtent(&extent);

		if (extent.Width > 0x1000 || extent.Height > 0x1000) {
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		ImageImplMode mode = this->imageImpl->GetMode();
		// if its rgba already, then just give the buffer
		if (mode == ImageImplMode::Rgba || mode == ImageImplMode::A) {
			this->imageImpl->ToBuffer(&pngBuffer);
		}
		else {
			// otherwise, convert to rgba then give buffer.
			this->imageImpl->ConvertMode(&extent, ImageImplMode::Rgba);
			this->imageImpl->ToBuffer(&pngBuffer);

		}

		return PSM_ERROR_NO_ERROR;

	}

	int Image::DrawRectangle(ImageColor color, ImageRect rect) {
		LOCK_GUARD();
		if (this->imageImpl == nullptr) return PSM_ERROR_COMMON_INVALID_OPERATION;

		if (this->imageImpl->GetMode() != ImageImplMode::Rgba && this->imageImpl->GetMode() != ImageImplMode::A) {
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}


		ImageSize size;
		this->imageImpl->GetExtent(&size);

		Logger::Debug("Filling range: " + std::to_string(rect.X) + "," + std::to_string(rect.Y) + "[" + std::to_string(rect.Width) + "x" + std::to_string(rect.Height) + "] with color: " + Format::Hex(color.ToUint32()));

		// caluclate absolute position on image.

		if (rect.X <= 0)
			rect.X = 0;

		if (rect.Y <= 0)
			rect.Y = 0;

		if (rect.Y + rect.Height > size.Height)
			rect.Height = size.Height;
		else
			rect.Height += rect.Y;


		if (rect.X + rect.Width > size.Width)
			rect.Width = size.Width;
		else
			rect.Width += rect.X;

		if (rect.X > size.Width) return PSM_ERROR_NO_ERROR;
		if (rect.Y > size.Height) return PSM_ERROR_NO_ERROR;

		this->normalizeColor(&color);


		// handle 1bpp alpha only image
		if (this->imageImpl->GetMode() == ImageImplMode::A) {
			for (int x = rect.X; x < rect.Width; x++) {
				for (int y = rect.Y; y < rect.Height; y++) {
					size_t pos = y + (x * size.Width);
					this->imageImpl->ImgBuffer[pos + 0] = color.A;
				}
			}
			return PSM_ERROR_NO_ERROR;
		}

		// handle full rgba image
		if (this->imageImpl->GetMode() == ImageImplMode::Rgba) {

			for (int y = rect.Y; y < rect.Height; y++) {
				for (int x = rect.X; x < rect.Width; x++) {
					size_t pos = y + (x * size.Width);
					this->imageImpl->ImgBuffer[pos + 0] = color.R;
					this->imageImpl->ImgBuffer[pos + 1] = color.G;
					this->imageImpl->ImgBuffer[pos + 2] = color.B;
					this->imageImpl->ImgBuffer[pos + 3] = color.A;
				}
			}

			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_NO_ERROR;
	}


	Image::Image(ImageMode mode, ImageSize* size, ImageColor* color) {		
		int channels = 0;
		ImageImplMode implMode = ImageImplMode::Rgba;

		if (mode > ImageMode::A) {
			SET_ERROR_AND_RETURN(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
		}

		if (mode == ImageMode::Rgba) {
			channels = 4;
			implMode = ImageImplMode::Rgba;
		}
		else if(mode == ImageMode::A) {
			channels = 1;
			implMode = ImageImplMode::A;
		}
		else {
			PANIC("Unknown image mode: " + std::to_string(static_cast<uint32_t>(mode)));
		}

		if ((size->Width < 0 || size->Width > 0x1000u) || (size->Height > 0x1000u)) {
			SET_ERROR_AND_RETURN(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
		}

		size_t bufferSize = channels * size->Width * size->Height;

		std::vector<uint8_t> img(bufferSize);
		if(img.data() != nullptr) {

			ImageColor colorNormalized = *color;
			this->normalizeColor(&colorNormalized);

			if (mode == ImageMode::A) {
				// check the size is valid?
				if (size->Width > 0 && size->Height > 0) {

					// loop over each coordinate of the image, and set the pixel to the right alpha.
					for (int y = 0; y < size->Height; y++) {
						for (int x = 0; x < size->Width; x++) {
							size_t pos = y + (x * size->Width) + 0;
							img.data()[pos] = colorNormalized.A;
						}
					}
				}
			}
			else if (mode == ImageMode::Rgba) {
				if (size->Width > 0 && size->Height > 0) { 	// check the size is valid?

					// loop over each coordinate of the image, and set the pixel to the right color.
					for (int y = 0; y < size->Height; y++) {
						for (int x = 0; x < size->Width; x++) {
							size_t pos = y + (x * size->Width);
							img.data()[pos + 0] = colorNormalized.R;
							img.data()[pos + 1] = colorNormalized.G;
							img.data()[pos + 2] = colorNormalized.B;
							img.data()[pos + 3] = colorNormalized.A;
						}
					}
				}

			}

			this->imageImpl = ImageImpl::CreateFromBuffer(img.data(), size, implMode, HeapAllocator::UniqueObject());
			SET_ERROR_AND_RETURN(this->Decode());
		}
		else {
			Logger::Error("ran out of memory;");
			SET_ERROR_AND_RETURN(PSM_ERROR_OUT_OF_MEMORY);
		}

	}

	int Image::GetPixelDataInternal(PixelData& data) {
		data.data = this->imageImpl->ImgBuffer;
		data.size = this->imageImpl->ImgBufferSize;
		return PSM_ERROR_NO_ERROR;
	}

	int Image::SetSize(const ImageSize& size) {
		
		if (size.Width < 0 || size.Width > 0x1000 || size.Height > 0x1000) {
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		if (this->imageImpl->SetDecExtent(size, 1))
			return PSM_ERROR_NO_ERROR;
		
		int err = ImageImpl::GetErrorType();
		if (err != PSM_ERROR_NO_ERROR) {
			this->SetError(err);
		}
		else {
			this->SetError(PSM_ERROR_COMMON_INVALID_OPERATION);
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		return err;
	}

	int Image::NewFromFilename(MonoString* filename, int* handle) {
		UNIMPLEMENTED();
	}
	int Image::NewFromFileImage(MonoArray* fileImage, int* handle) {
		UNIMPLEMENTED();
	}
	int Image::NewFromModeSizeColor(ImageMode mode, ImageSize* size, ImageColor* color, int* handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		Image* img = Image::Create(mode, size, color);
		RETURN_ERRORABLE_PSMOBJECT(img, Image);
		*handle = img->Handle();
		
		return PSM_ERROR_NO_ERROR;
	}
	int Image::NewFromModeSizeBuffer(ImageMode mode, ImageSize* size, MonoArray* buffer, int* handle) {
		UNIMPLEMENTED();
	}
	int Image::AddRefNative(int handle){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		Image::AddRef(handle);
		return PSM_ERROR_NO_ERROR;
	}
	int Image::ReleaseNative(int handle){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();
		
		Image::Delete(handle);
		return PSM_ERROR_NO_ERROR;
	}

	int Image::GetSize(int handle, ImageSize* size){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();
		if (!Image::CheckHandle(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}
		Image* img = Image::LookupHandle(handle);
		*size = img->Size();
		return PSM_ERROR_NO_ERROR;
	}



	int Image::SetDecodeSize(int handle, ImageSize* size) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Image::CheckHandle(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		Image* img = Image::LookupHandle(handle);
		return img->SetSize(*size);
	}
	int Image::DecodeNative(int handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Image::CheckHandle(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		return Image::LookupHandle(handle)->Decode();
	}

	int Image::GetPixelData(int handle, MonoArray* buffer, uint32_t bufferSize) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		PixelData pixelData;

		if (!Image::CheckHandle(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		Image* img = Image::LookupHandle(handle);
		img->GetPixelDataInternal(pixelData);
		
		if (bufferSize >= pixelData.size) {
			char* buf = mono_array_addr_with_size(buffer, 1, 0);
			size_t length = mono_array_length(buffer);
			memcpy(buf, pixelData.data, pixelData.size);
		}

		return PSM_ERROR_NO_ERROR;
	}
	int Image::GetPixelDataSize(int handle, uint32_t* bufferSize) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		PixelData pixelData;

		if (!Image::CheckHandle(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		Image* img = Image::LookupHandle(handle);
		img->GetPixelDataInternal(pixelData);

		*bufferSize = pixelData.size;

		return PSM_ERROR_NO_ERROR;
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
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Image::CheckHandle(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		Image* img = Image::LookupHandle(handle);
		return img->DrawRectangle(*color, *rect);
	}

#ifdef COMPAT_VITA_2_01_RUNTIME_FEATURES
	int Image::DrawTextNative(int handle, MonoString* text, uint32_t offset, uint32_t len, ImageColor* color, int font_handle, ImagePosition* position) {
#else
	int Image::DrawTextNative(int handle, MonoString * text, int offset, int len, ImageColor * color, int font_handle, ImagePosition * position) {
#endif
		UNIMPLEMENTED();
	}
	int Image::ExportNative(int handle, MonoString* albumname, MonoString* filename) {
		UNIMPLEMENTED();
	}
	int Image::SaveAsNative(int handle, MonoString* filename) {
		UNIMPLEMENTED();
	}
}
