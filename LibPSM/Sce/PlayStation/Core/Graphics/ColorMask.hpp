#ifndef LIB_PSM_COLORMASK_H
#define LIB_PSM_COLORMASK_H
#include <string>

namespace Sce::PlayStation::Core::Graphics {
	enum class ColorMask : uint8_t {
		None = 0x0,
		R = 0x1,
		G = 0x2,
		B = 0x4,
		A = 0x8,
		Rgb = 0x7,
		Rgba = 0xF,
	};


	ColorMask operator&(ColorMask l, ColorMask r);
	ColorMask operator&(ColorMask l, uint8_t r);
	ColorMask operator&(uint8_t l, ColorMask r);

	ColorMask operator|(ColorMask l, ColorMask r);
	ColorMask operator|(uint8_t l, ColorMask r);
	ColorMask operator|(ColorMask l, uint8_t r);
}

#endif