#ifndef LIB_PSM_BLENDFUNCFACTOR_H
#define LIB_PSM_BLENDFUNCFACTOR_H
#include <string>

namespace Sce::PlayStation::Core::Graphics {
	enum class BlendFuncFactor : uint8_t {
		Zero = 0,
		One = 1,
		SrcColor = 2,
		OneMinusSrcColor = 3,
		SrcAlpha = 4,
		OneMinusSrcAlpha = 5,
		DstColor = 6,
		OneMinusDstColor = 7,
		DstAlpha = 8,
		OneMinusDstAlpha = 9,
		SrcAlphaSaturate = 10
	};
}

#endif