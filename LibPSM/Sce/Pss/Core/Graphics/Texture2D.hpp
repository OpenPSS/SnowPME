#ifndef LIB_PSS_TEXTURE_2D_H
#define LIB_PSS_TEXTURE_2D_H 1

#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class Texture2D : public Texture {
	private:

	public:
		Texture2D(std::string fileName, bool mipmap, Sce::PlayStation::Core::Graphics::PixelFormat format);
		~Texture2D();
		GLenum GlTextureType();
		int ActiveStateChanged(bool state);
	};
}

#endif