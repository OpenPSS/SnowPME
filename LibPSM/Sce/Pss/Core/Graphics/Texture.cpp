#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {

	Texture::Texture() {

	}

	Texture::~Texture() {

	}

	uint32_t Texture::GlTextureType() {
		return GL_TEXTURE_2D;
	}

}