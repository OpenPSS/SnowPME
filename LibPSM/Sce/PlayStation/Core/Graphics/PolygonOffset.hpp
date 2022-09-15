#ifndef LIB_PSM_POLYGONOFFSET_H
#define LIB_PSM_POLYGONOFFSET_H
#include <string>

namespace Sce::PlayStation::Core::Graphics {
	typedef struct PolygonOffset {
		float Factor;
		float Units;
	} PolygonOffset;
}

#endif