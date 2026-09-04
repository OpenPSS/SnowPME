#ifndef LIB_PSS_DRAWMODE_H
#define LIB_PSS_DRAWMODE_H

#include <Sce/Pss/Core/BitwiseEnum.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Graphics {
	enum class DrawMode : uint16_t {
		Points = 0,
		Lines = 1,
		LineStrip = 2,
		Triangles = 3,
		TriangleStrip = 4,
		TriangleFan = 5
	};

	DEFINE_BITWISE_ENUM_OPERATOR(DrawMode, unsigned short);
}

#endif