#ifndef LIB_PSM_STENCILFUNCMODE_H
#define LIB_PSM_STENCILFUNCMODE_H 1
#include <string>
namespace Sce::PlayStation::Core::Graphics {
	enum class StencilFuncMode : uint8_t {
		Always = 0,
		Never = 1,
		Equal = 2,
		NotEqual = 3,
		Less = 4,
		Greater = 5,
		LEqual = 6,
		GEqual = 7,
		NotEequal = 3
	};
}

#endif