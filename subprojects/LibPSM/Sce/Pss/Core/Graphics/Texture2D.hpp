#ifndef LIB_PSS_TEXTURE_2D_H
#define LIB_PSS_TEXTURE_2D_H 1

#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/Imaging/Impl/Image.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class Texture2D : public Texture {
	private:
		Sce::Pss::Core::Imaging::Impl::Image image;

	public:
		Texture2D(std::string* fileName, bool mipmap, Sce::Pss::Core::Graphics::PixelFormat format);
		~Texture2D();
		//int InitImage();
		int LoadImage(uint8_t* data, uint32_t dataLen, bool mipmap, Sce::Pss::Core::Graphics::PixelFormat format);
		GLenum GlTextureType();
		int ActiveStateChanged(bool state);
	};
}

#endif