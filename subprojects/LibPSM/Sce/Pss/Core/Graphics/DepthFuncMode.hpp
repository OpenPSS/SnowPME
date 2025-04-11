#ifndef LIB_PSS_DEPTHFUNCMODE_H
#define LIB_PSS_DEPTHFUNCMODE_H
#include <string>

namespace Sce::Pss::Core::Graphics {
	enum class DepthFuncMode : uint8_t {
		Always = 0,
		Never = 1,
		Equal = 2,
		NotEqual = 3,
		Less = 4,
		Greater = 5,
		LEqual = 6,
		GEqual = 7,
		NotEequal = 8
	};
}

#endif