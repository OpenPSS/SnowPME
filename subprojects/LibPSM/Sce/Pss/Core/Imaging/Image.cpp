#include <Sce/Pss/Core/Imaging/Image.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <cstdint>
#include <string>
#include <cstdio>

using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Imaging::Impl;

namespace Sce::Pss::Core::Imaging {

	void Image::normalizeColor(ImageColor* color) {
		
		if (color->R >= 255) color->R = 255;
		else color->R = (color->R < 0 ? 0 : color->R);

		if (color->G >= 255) color->G = 255;
		else color->G = (color->G < 0 ? 0 : color->G);

		if (color->B >= 255) color->B = 255;
		else color->B = (color->B < 0 ? 0 : color->B);

		if (color->A >= 255) color->A = 255;
		else color->A = (color->A < 0 ? 0 : color->A);

	}

	int Image::Decode() {
		UNIMPLEMENTED();
	}


	Image::Image(ImageMode mode, ImageSize* size, ImageColor* color) {		
		int channels = 0;
		int unk1 = 0;

		if (mode > ImageMode::A) {
			SET_ERROR_AND_RETURN(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
		}

		if (mode == ImageMode::Rgba) {
			channels = 4;
			unk1 = 4;
		}
		else if(mode == ImageMode::A) {
			channels = 1;
			unk1 = 14;
		}

		if ((size->Width < 0 || size->Width > 0x1000) || (size->Height > 0x1000)) {
			SET_ERROR_AND_RETURN(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
		}

		int imageBufferSize = channels * size->Width * size->Height;
		uint8_t* imageData = reinterpret_cast<uint8_t*>(HeapAllocator::UniqueObject()->sce_psm_malloc(imageBufferSize));
		if(imageData != nullptr) {

			ImageColor colorNormalized = *color;
			this->normalizeColor(&colorNormalized);

			if (mode == ImageMode::A) {
				// check the size is valid?
				if (size->Width > 0 && size->Height > 0) {

					// loop over each coordinate of the image, and set the pixel to the right alpha.
					for (int y = 0; y < size->Height; y++) {
						for (int x = 0; x < size->Width; x++) {
							imageData[y + (x * size->Width) + 0] = colorNormalized.A;
						}
					}
				}
			}
			else if (mode == ImageMode::Rgba) {
				// check the size is valid?
				if (size->Width > 0 && size->Height > 0) {

					// loop over each coordinate of the image, and set the pixel to the right color.
					for (int y = 0; y < size->Height; y++) {
						for (int x = 0; x < size->Width; x++) {
							imageData[y + (x * size->Width) + 0] = colorNormalized.R;
							imageData[y + (x * size->Width) + 1] = colorNormalized.G;
							imageData[y + (x * size->Width) + 2] = colorNormalized.B;
							imageData[y + (x * size->Width) + 3] = colorNormalized.A;
						}
					}
				}

			}

			this->image = ImageImpl::CreateFromBuffer(imageData, size, channels, HeapAllocator::UniqueObject());
			HeapAllocator::UniqueObject()->sce_psm_free(imageData);
			SET_ERROR_AND_RETURN(this->Decode());
		}
		else {
			SET_ERROR_AND_RETURN(PSM_ERROR_OUT_OF_MEMORY);
		}

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

		std::shared_ptr<Image> img = Image::Create(mode, size, color);
		RETURN_ERRORABLE_PSMOBJECT(img, Image);
		*handle = img->Handle();
		
		return PSM_ERROR_NO_ERROR;
	}
	int Image::NewFromModeSizeBuffer(ImageMode mode, ImageSize* size, MonoArray* buffer, int* handle) {
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
	int Image::DrawTextNative(int handle, MonoString* text, int offset, int len, ImageColor* color, int font_handle, ImagePosition* position) {
		UNIMPLEMENTED();
	}
	int Image::ExportNative(int handle, MonoString* albumname, MonoString* filename) {
		UNIMPLEMENTED();
	}
	int Image::SaveAsNative(int handle, MonoString* filename) {
		UNIMPLEMENTED();
	}
}
