#ifndef LIB_PSM_TEXTUREWRAPMODE_H
#define LIB_PSM_TEXTUREWRAPMODE_H 1
#include <string>
namespace Sce::PlayStation::Core::Graphics {
	enum class TextureWrapMode : uint8_t {
		ClampToEdge = 0,
		Repeat = 1
	};
}

#endif