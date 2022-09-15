#ifndef LIB_PSM_ENABLEMODE_H
#define LIB_PSM_ENABLEMODE_H

namespace Sce::PlayStation::Core::Graphics {
	enum class EnableMode : unsigned int {
		None = 0,
		ScissorTest = 1,
		CullFace = 2,
		Blend = 4,
		DepthTest = 8,
		PolygonOffsetFill = 16,
		StencilTest = 32,
		Dither = 64,
		All = 127
	};
}

#endif