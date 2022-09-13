#ifndef LIB_PSM_BLENDFUNCMODE_H
#define LIB_PSM_BLENDFUNCMODE_H
#include <string>

namespace Sce::PlayStation::Core::Graphics {
	enum class BlendFuncMode : uint8_t {
		Add = 0,
		Subtract = 1,
		ReverseSubtract = 2
	};
}

#endif