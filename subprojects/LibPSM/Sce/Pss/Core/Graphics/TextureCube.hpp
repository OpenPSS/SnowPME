#ifndef LIB_PSS_TEXTURE_CUBE_H
#define LIB_PSS_TEXTURE_CUBE_H 1

#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class TextureCube : public Texture, public PsmObject<TextureCube> {
	private:

	public:
		
		TextureCube(std::string& fileName, bool mipmap, Sce::Pss::Core::Graphics::PixelFormat format);
		~TextureCube();
		GLenum GLTextureType();
		int ActiveStateChanged(bool state);
	};
}

#endif