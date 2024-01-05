#ifndef LIB_PSS_POLYGONOFFSET_H
#define LIB_PSS_POLYGONOFFSET_H
#include <string>

namespace Sce::Pss::Core::Graphics {
	typedef struct PolygonOffset {
		float Factor;
		float Units;
	} PolygonOffset;
}

#endif