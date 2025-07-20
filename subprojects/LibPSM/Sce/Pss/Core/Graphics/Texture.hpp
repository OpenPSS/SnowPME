#ifndef LIB_PSS_TEXTURE_H
#define LIB_PSS_TEXTURE_H 1
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class Texture : public PixelBuffer {
	public:
		int ActiveStateChanged(bool state);

		Texture();
		virtual ~Texture() = default;
	};
}

#endif
