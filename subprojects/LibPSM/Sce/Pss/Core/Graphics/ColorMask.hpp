#ifndef LIB_PSS_COLORMASK_H
#define LIB_PSS_COLORMASK_H
#include <string>
#include <cstdint>
#include <Sce/Pss/Core/BitwiseEnum.hpp>


namespace Sce::Pss::Core::Graphics {
	enum class ColorMask : uint8_t {
		None = 0x0,
		R = 0x1,
		G = 0x2,
		B = 0x4,
		A = 0x8,
		Rgb = 0x7,
		Rgba = 0xF,
	};

	DEFINE_BITWISE_ENUM_OPERATOR(ColorMask, uint8_t);
}

#endif