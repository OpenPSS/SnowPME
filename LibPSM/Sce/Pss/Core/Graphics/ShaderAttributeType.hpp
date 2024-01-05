#ifndef LIB_PSS_SHADERATTRIBUTETYPE_H
#define LIB_PSS_SHADERATTRIBUTETYPE_H 1

namespace Sce::Pss::Core::Graphics {
	enum class ShaderAttributeType : unsigned int {
		None = 0,
		Float = 0x100,
		Float2 = 257,
		Float3 = 258,
		Float4 = 259
	};
}

#endif