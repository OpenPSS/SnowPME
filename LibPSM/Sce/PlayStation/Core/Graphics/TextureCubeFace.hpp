#ifndef LIB_PSM_TEXTURECUBEFACE_H
#define LIB_PSM_TEXTURECUBEFACE_H 1
#include <string>
namespace Sce::PlayStation::Core::Graphics {
	enum class TextureCubeFace : uint8_t {
		PositiveX = 0,
		NegativeX = 1,
		PositiveY = 2,
		NegativeY = 3,
		PositiveZ = 4,
		NegativeZ = 5
	};
}

#endif