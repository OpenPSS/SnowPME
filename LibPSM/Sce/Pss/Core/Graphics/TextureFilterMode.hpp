#ifndef LIB_PSS_TEXTUREFILTERMODE_H
#define LIB_PSS_TEXTUREFILTERMODE_H 1
#include <string>
namespace Sce::Pss::Core::Graphics {
	enum class TextureFilterMode : uint8_t {
		Nearest = 0,
		Linear = 1,
		Disabled = 2
	};
}

#endif