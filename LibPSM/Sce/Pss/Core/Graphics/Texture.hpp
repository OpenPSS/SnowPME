#ifndef LIB_PSS_TEXTURE_H
#define LIB_PSS_TEXTURE_H 1
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/PlayStation/Core/Graphics/PixelFormat.hpp>
#include <glad/glad.h>
namespace Sce::Pss::Core::Graphics {
	class Texture : public GraphicsObject {
	private:
	public:
		virtual GLenum GlTextureType() = NULL;
		std::string Filename;
		int ActiveStateChanged(bool state);

		Texture();
		~Texture();
	};
}

#endif