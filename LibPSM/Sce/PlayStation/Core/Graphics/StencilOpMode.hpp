#ifndef LIB_PSM_STENCILOPMODE_H
#define LIB_PSM_STENCILOPMODE_H 1
#include <string>
namespace Sce::PlayStation::Core::Graphics {
	enum class StencilOpMode : uint8_t {
		Keep = 0,
		Zero = 1,
		Replace = 2,
		Invert = 3,
		Incr = 4,
		Decr = 5,
		IncrWrap = 6,
		DecrWrap = 7
	};
}

#endif