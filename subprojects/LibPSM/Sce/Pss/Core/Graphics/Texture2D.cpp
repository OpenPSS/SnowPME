#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Imaging/Impl/ImageImpl.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsCapsState.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>

#include <glad/glad.h>
#include <LibShared.hpp>
#include <string.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Imaging;
using namespace Sce::Pss::Core::Imaging::Impl;

namespace Sce::Pss::Core::Graphics {



	Texture2D::Texture2D(int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, Sce::Pss::Core::Graphics::InternalOption option2) {
		LOCK_GUARD();
		this->InitImage(width, height, mipmap, format, option, option2, 0);
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


	int Texture2D::InitImage(int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption intOption, int unk0) {
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
			(!this->GetFormatHasRgb(format) || this->GetFormatHasHalfFloat(format))) {
			ExceptionInfo::AddMessage("Unsupported format for renderable texture\n");
			return this->SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
		}

		if (!CheckFormatSizeError(format, width, height))
			return PSM_ERROR_NO_ERROR;

		this->option = option;
		this->type = PixelBufferType::Texture2D;
		this->format = format;
		this->width = width;
		this->height = height;

		int mipmapLevel = 1;
		if (mipmap != 0) {
			mipmapLevel = this->CalculateTotalMipMaps(width, height);
		}

		this->mipmapLevel = mipmapLevel;
		this->unk11 = 1;
		this->glPixelBufferType = GL_TEXTURE_2D;
		
		GraphicsExtension extension = GraphicsContext::GetCaps().Extension;

		if (this->GetFormatHasHalfFloat(format)) {
			this->needsHalfFloat = ((extension & GraphicsExtension::TextureHalfFloat) == GraphicsExtension::None);
		}

		// TODO: Figure out why PSM Checks this?? 
		if (((width - 1) & width) != 0 || ((height - 1) & height) != 0) {
			this->usesRgba = (extension & GraphicsExtension::TextureNpot) == GraphicsExtension::None;
			if (extension < GraphicsExtension::None)
				this->mipmapLevel = 1;
		}


		// clear all gl errors
		while (glGetError());

		// generate GL Handle ...
		glGenTextures(1, &this->GLHandle);

		int formatComponent = OpenGL::GetTextureFormatComponent(format);
		int formatType = OpenGL::GetTextureFormatType(format);
		int bitsPerPixel = this->GetFormatBitsPerPixel(format);

		PixelFormat pixFormat = (format < PixelFormat::Dxt1) ? PixelFormat::None : PixelFormat::Rgba4444;
		
		// start using this texture
		Texture* prev = OpenGL::SetTexture(this);

		// generate mipmaps
		if (mipmapLevel > 0) {
			// TODO: Implement mipmap part of the code (it looks scary...)
			UNIMPLEMENTED_MSG("Generation of mip maps is not yet implemented");
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

		return this->CheckGlError() && this->AllocCache(intOption);
	}


	int Texture2D::ActiveStateChanged(bool state) {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

}
