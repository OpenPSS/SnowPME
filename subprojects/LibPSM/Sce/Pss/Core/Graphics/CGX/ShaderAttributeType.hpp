#ifndef LIB_PSS_SHADERATTRIBUTETYPE_H
#define LIB_PSS_SHADERATTRIBUTETYPE_H 1
#include <Sce/Pss/Core/BitwiseEnum.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobalType.hpp>

namespace Sce::Pss::Core::Graphics::CGX {
	enum class ShaderAttributeType : uint32_t {
		None = 0x0,
		Float = 0x100,
		Float2 = 0x101,
		Float3 = 0x102,
		Float4 = 0x103,
	};

	DEFINE_BITWISE_ENUM_OPERATOR(ShaderAttributeType, uint32_t);
}

#endif