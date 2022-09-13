#ifndef LIB_PSM_SHADERATTRIBUTETYPE_H
#define LIB_PSM_SHADERATTRIBUTETYPE_H 1

namespace Sce::PlayStation::Core::Graphics {
	enum class ShaderAttributeType : unsigned int {
		None = 0,
		Float = 0x100,
		Float2 = 257,
		Float3 = 258,
		Float4 = 259
	};
}

#endif