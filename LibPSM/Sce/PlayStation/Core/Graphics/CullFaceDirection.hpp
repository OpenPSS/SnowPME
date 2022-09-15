#ifndef LIB_PSM_CULLFACEDIRECTION_H
#define LIB_PSM_CULLFACEDIRECTION_H
#include <string>

namespace Sce::PlayStation::Core::Graphics {
	enum class CullFaceDirection : uint8_t {
		Cw = 0,
		Ccw = 1
	};
}

#endif