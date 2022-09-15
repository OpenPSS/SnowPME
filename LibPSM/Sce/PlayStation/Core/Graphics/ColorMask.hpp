#ifndef LIB_PSM_COLORMASK_H
#define LIB_PSM_COLORMASK_H
#include <string>

namespace Sce::PlayStation::Core::Graphics {
	enum class ColorMask : uint8_t {
		None = 0,
		R = 1,
		G = 2,
		B = 4,
		A = 8,
		Rgb = 7,
		Rgba = 15
	};
}

#endif