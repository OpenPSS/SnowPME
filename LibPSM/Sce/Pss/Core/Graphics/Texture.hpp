#ifndef LIB_PSM_TEXTURE_H
#define LIB_PSM_TEXTURE_H 1
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>

namespace Sce::Pss::Core::Graphics {
	class Texture : public GraphicsObject {
	private:
		
	public:
		uint32_t GlTextureType();

		Texture();
		~Texture();
	};
}

#endif