#ifndef LIB_PSS_SHADERATTRIBUTETYPE_H
#define LIB_PSS_SHADERATTRIBUTETYPE_H 1
#include <Sce/Pss/Core/BitwiseEnum.hpp>

namespace Sce::Pss::Core::Graphics {
	enum class ShaderAttributeType : unsigned int {
		None = 0,
		Float = 0x100,
		Float2 = 257,
		Float3 = 258,
		Float4 = 259
	};

	DEFINE_BITWISE_ENUM_OPERATOR(ShaderAttributeType, unsigned int);
}

#endif