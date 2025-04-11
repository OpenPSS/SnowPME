#ifndef LIB_PSS_BLENDFUNCMODE_H
#define LIB_PSS_BLENDFUNCMODE_H
#include <string>

namespace Sce::Pss::Core::Graphics {
	enum class BlendFuncMode : uint8_t {
		Add = 0,
		Subtract = 1,
		ReverseSubtract = 2
	};
}

#endif