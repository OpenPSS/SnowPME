#ifndef LIB_PSM_COLORMASK_H
#define LIB_PSM_COLORMASK_H
#include <string>
#include <Sce/Pss/Core/BitwiseEnum.hpp>


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

	DefineBitwiseOperators(ColorMask, uint8_t);
}

#endif