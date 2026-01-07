#ifndef LIB_PSS_PIXELFORMAT_H
#define LIB_PSS_PIXELFORMAT_H 1
#include <Sce/Pss/Core/BitwiseEnum.hpp>
#include <cstdint>
namespace Sce::Pss::Core::Graphics {

	enum class PixelFormat : uint32_t
	{
		None = 0x0,
		Rgba = 0x1,
		RgbaH = 0x2,
		Rgba4444 = 0x3,
		Rgba5551 = 0x4,
		Rgb565 = 0x5,
		LuminanceAlpha = 0x6,
		LuminanceAlphaH = 0x7,
		Luminance = 0x8,
		LuminanceH = 0x9,
		Alpha = 0xA,
		AlphaH = 0xB,
		Depth16 = 0xC,
		Depth24 = 0xD,
		Depth16Stencil8 = 0xE,
		Depth24Stencil8 = 0xF,
		Dxt1 = 0x10,
		Dxt2 = 0x11,
		Dxt3 = 0x12,
		Dxt4 = 0x13,
		Dxt5 = 0x14,
	};
	
	DEFINE_BITWISE_ENUM_OPERATOR(PixelFormat, uint32_t);
}

#endif