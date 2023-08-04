#ifndef LIB_PSS_TEXTURE_CUBE_H
#define LIB_PSS_TEXTURE_CUBE_H 1

#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class TextureCube : public Texture {
	private:

	public:
		TextureCube(std::string fileName, bool mipmap, Sce::PlayStation::Core::Graphics::PixelFormat format);
		~TextureCube();
		GLenum GlTextureType();
		int ActiveStateChanged(bool state);
	};
}

#endif