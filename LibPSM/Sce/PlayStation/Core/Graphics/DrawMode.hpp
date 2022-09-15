#ifndef LIB_PSM_DRAWMODE_H
#define LIB_PSM_DRAWMODE_H

namespace Sce::PlayStation::Core::Graphics {
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