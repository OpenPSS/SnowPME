#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Imaging/Impl/ImageImpl.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsCapsState.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <Sce/Pss/Core/Features.hpp>

#include <glad/glad.h>
#include <LibShared.hpp>
#include <string.h>
#include <cmath>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Imaging;
using namespace Sce::Pss::Core::Imaging::Impl;

namespace Sce::Pss::Core::Graphics {

	Texture2D::Texture2D(int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption internalOption) {
		LOCK_GUARD();
		LOG_FUNCTION();
		this->InitImage(width, height, mipmap, format, option, internalOption, nullptr);
	}

	Texture2D::Texture2D(std::string& fileName, bool mipmap, PixelFormat format) {
		LOCK_GUARD();

		if (!fileName.empty()) {
			this->filename = std::string(fileName.c_str(), strlen(fileName.c_str()));
			this->glPixelBufferType = GL_TEXTURE_2D;

			uint8_t* fileData = nullptr;
			uint32_t fileSize = 0;

			// load the file data
			int res = this->LoadFile(this->filename.c_str(), fileData, fileSize);
			if (res == PSM_ERROR_NO_ERROR) {

				// parse image file 
				this->LoadImage(fileData, fileSize, mipmap, format);

				// free the file data
				std::shared_ptr<HeapAllocator> allocator = HeapAllocator::UniqueObject();
				allocator->sce_psm_free(fileData);
			}
			else {
				this->SetError(res);
			}
		}
		else {
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_NULL);
		}
	}

	int Texture2D::LoadImage(uint8_t* data, uint32_t dataLen, bool mipmap, PixelFormat format) {
		LOG_FUNCTION();

		this->imageImpl = ImageImpl::Open(data, dataLen, HeapAllocator::UniqueObject());
		RETURN_ERRORABLE_SMARTPTR(this->imageImpl);

		UNIMPLEMENTED();
	}


	int Texture2D::InitImage(int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption intOption, void* unk0) {
		LOG_FUNCTION();
		
		if (!this->CheckSizeError(width, height, 0, 0x800)) {
			return PSM_ERROR_NO_ERROR;
		}

		if (!this->CheckFormatError(format, option)) {
			return PSM_ERROR_NO_ERROR;
		}

		if (format == PixelFormat::None || this->GetFormatHasDepth(format)) {
			ExceptionInfo::AddMessage("Unsupported format\n");
			return this->SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
		}

		if ((option & PixelBufferOption::Renderable) != PixelBufferOption::None &&
			(!PixelBuffer::GetFormatHasRgb(format) || PixelBuffer::GetFormatHasHalfFloat(format))) {
			ExceptionInfo::AddMessage("Unsupported format for renderable texture\n");
			return this->SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
		}

		if (!this->CheckFormatSizeError(format, width, height))
			return PSM_ERROR_NO_ERROR;

		this->option = option;
		this->type = PixelBufferType::Texture2D;
		this->format = format;
		this->width = width;
		this->height = height;


		int mipmapLevel = 1;
		if (mipmap != false) {
			mipmapLevel = PixelBuffer::CalculateTotalMipMaps(width, height);
		}

		this->mipmapLevel = mipmapLevel;
		this->glPixelBufferType = GL_TEXTURE_2D;
		this->unk11 = 1;

		Logger::Debug("this->Option: " + Format::Hex(static_cast<int>(this->option)));
		Logger::Debug("this->Type: " + Format::Hex(static_cast<int>(this->type)));
		Logger::Debug("this->Format: " + Format::Hex(static_cast<int>(this->format)));
		Logger::Debug("this->Width: " + Format::Hex(static_cast<int>(this->width)));
		Logger::Debug("this->Height: " + Format::Hex(static_cast<int>(this->height)));

		GraphicsExtension extension = GraphicsContext::GetCaps().Extension;

		if (PixelBuffer::GetFormatHasHalfFloat(format)) {
			this->needsHalfFloat = ((extension & GraphicsExtension::TextureHalfFloat) == GraphicsExtension::None);
		}

		if (!PixelBuffer::CheckPowerOfTwo(width, height)) {
			this->npot = (extension & GraphicsExtension::TextureNpot) == GraphicsExtension::None;
			if (extension < GraphicsExtension::None)
				this->mipmapLevel = 1;
		}


		// clear all gl errors
		while (glGetError());

		// generate GL Handle ...
		glGenTextures(1, &this->GLHandle);

		int formatComponent = OpenGL::GetTextureFormatComponent(format);
		int formatType = OpenGL::GetTextureFormatType(format);
		int bitsPerPixel = PixelBuffer::GetFormatBitsPerPixel(format);

		Logger::Debug("formatComponent: 0x" + Format::Hex(formatComponent));
		Logger::Debug("formatType: 0x" + Format::Hex(formatType));
		Logger::Debug("bitsPerPixel: 0x" + Format::Hex(bitsPerPixel));


		// start using this texture
		Texture* prev = OpenGL::SetTexture(this);

		// generate mipmaps
		if (mipmapLevel > 0) {

			for (int i = 0; i <= this->mipmapLevel; i++) {
				Logger::Debug("Generating MipMap " + std::to_string(i)+ " of " + std::to_string(this->mipmapLevel));

				// require valid positive number for height
				if (width < 1) width = 1;
				if (height < 1) height = 1;

				// TODO: if(unk0 != null, pixels = *(unk0 + 0x1c);
				if (unk0 != nullptr) UNIMPLEMENTED_MSG("unk0 != null unimplemented if(unk0 != null, pixels = *(unk0 + 0x1c);");
				GLvoid* pixels = nullptr;

				// calculate size including compressions;
				this->imageSize += PixelBuffer::CalculateImageArraySizeInBytes(format, bitsPerPixel, width, height);

				// generate current mipmap;
				if (PixelBuffer::IsFormatDxt(format)) {
					glCompressedTexImage2D(this->glPixelBufferType, i, formatComponent, width, height, 0, this->imageSize, pixels);
				}
				else {
					glTexImage2D(this->glPixelBufferType, i, formatComponent, width, height, 0, formatComponent, formatType, pixels);
				}

				// half the image size for the next mipmap;

				width /= 2;
				height /= 2;

				// if there is an error in OpenGL
				if (!this->CheckGLError()) {
					OpenGL::SetTexture(prev);
					return PSM_ERROR_NO_ERROR;
				}
				else if (glGetError() != GL_NO_ERROR) { // can this even run? 
					this->mipmapLevel = 1;
				}
			}
		}

		bool needsHalfFloat = this->needsHalfFloat;
		bool needsMipMap = this->mipmapLevel > 1;

		GLenum minFilter = GL_NONE;
		GLenum magFilter = needsHalfFloat ? GL_NEAREST : GL_LINEAR;

		if (needsHalfFloat)
			minFilter = needsMipMap ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
		else
			minFilter = needsMipMap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;


		glTexParameteri(this->glPixelBufferType, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexParameteri(this->glPixelBufferType, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(this->glPixelBufferType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->glPixelBufferType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// change texture back to prebious texture
		OpenGL::SetTexture(prev);

		return this->CheckGLError() && this->AllocCache(intOption);
	}


	int Texture2D::ActiveStateChanged(bool state) {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

}
