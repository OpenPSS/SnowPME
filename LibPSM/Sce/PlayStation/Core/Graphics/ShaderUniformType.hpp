#ifndef LIB_PSM_SHADERUNIFORMTYPE_H
#define LIB_PSM_SHADERUNIFORMTYPE_H 1

namespace Sce::PlayStation::Core::Graphics {
	enum class ShaderUniformType : unsigned int {
		None = 0,
		Float = 0x100,
		Float2 = 257,
		Float3 = 258,
		Float4 = 259,
		Float2x2 = 273,
		Float3x3 = 290,
		Float4x4 = 307,
		Int = 0x400,
		Int2 = 1025,
		Int3 = 1026,
		Int4 = 1027,
		Bool = 768,
		Bool2 = 769,
		Bool3 = 770,
		Bool4 = 771,
		Sampler2D = 32769,
		SamplerCube = 32770
	};
}

#endif