#ifndef LIB_PSS_TEXTURECUBEFACE_H
#define LIB_PSS_TEXTURECUBEFACE_H 1
#include <string>
#include <cstdint>
namespace Sce::Pss::Core::Graphics {
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