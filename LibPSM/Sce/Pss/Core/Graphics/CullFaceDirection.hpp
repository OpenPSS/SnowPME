#ifndef LIB_PSS_CULLFACEDIRECTION_H
#define LIB_PSS_CULLFACEDIRECTION_H
#include <string>

namespace Sce::Pss::Core::Graphics {
	enum class CullFaceDirection : uint8_t {
		Cw = 0,
		Ccw = 1
	};
}

#endif