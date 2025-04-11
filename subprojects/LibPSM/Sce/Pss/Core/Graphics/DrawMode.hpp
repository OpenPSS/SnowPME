#ifndef LIB_PSS_DRAWMODE_H
#define LIB_PSS_DRAWMODE_H

namespace Sce::Pss::Core::Graphics {
	enum class DrawMode : unsigned short {
		Points = 0,
		Lines = 1,
		LineStrip = 2,
		Triangles = 3,
		TriangleStrip = 4,
		TriangleFan = 5
	};
}

#endif