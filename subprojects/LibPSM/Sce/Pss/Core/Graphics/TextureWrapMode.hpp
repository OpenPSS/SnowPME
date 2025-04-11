#ifndef LIB_PSS_TEXTUREWRAPMODE_H
#define LIB_PSS_TEXTUREWRAPMODE_H 1
#include <string>
namespace Sce::Pss::Core::Graphics {
	enum class TextureWrapMode : uint8_t {
		ClampToEdge = 0,
		Repeat = 1
	};
}

#endif