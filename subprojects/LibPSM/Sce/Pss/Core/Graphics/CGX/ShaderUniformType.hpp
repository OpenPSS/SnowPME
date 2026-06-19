#ifndef LIB_PSS_SHADER_UNIFORM_TYPE_H
#define LIB_PSS_SHADER_UNIFORM_TYPE_H 1
#include <Sce/Pss/Core/BitwiseEnum.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobalType.hpp>

namespace Sce::Pss::Core::Graphics::CGX {
	enum class ShaderUniformType : uint32_t {
		None = 0x0,
		Float = 0x100,
		Float2 = 0x101,
		Float3 = 0x102,
		Float4 = 0x103,
		Float2x2 = 0x111,
		Float3x3 = 0x122,
		Float4x4 = 0x133,
		Int = 0x400,
		Int2 = 0x401,
		Int3 = 0x402,
		Int4 = 0x403,
		Bool = 0x300,
		Bool2 = 0x301,
		Bool3 = 0x302,
		Bool4 = 0x303,
		Sampler2D = 0x8001,
		SamplerCube = 0x8002
	};

	DEFINE_BITWISE_ENUM_OPERATOR(ShaderUniformType, uint32_t);
}

#endif