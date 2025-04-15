#ifndef LIB_PSS_ENABLEMODE_H
#define LIB_PSS_ENABLEMODE_H
#include <Sce/Pss/Core/BitwiseEnum.hpp>

namespace Sce::Pss::Core::Graphics {
	enum class EnableMode : unsigned int {
		None = 0x0,
		ScissorTest = 0x1,
		CullFace = 0x2,
		Blend = 0x4,
		DepthTest = 0x8,
		PolygonOffsetFill = 0x10,
		StencilTest = 0x20,
		Dither = 0x40,
		All = 0x7F
	};

	DEFINE_BITWISE_OPERATORS(EnableMode, unsigned int);
}

#endif