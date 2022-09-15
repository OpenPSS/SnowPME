#ifndef LIB_PSM_PIXELFORMAT_H
#define LIB_PSM_PIXELFORMAT_H 1

namespace Sce::PlayStation::Core::Graphics {
	enum class PixelFormat : unsigned int {
		None = 0,
		Rgba = 1,
		RgbaH = 2,
		Rgba4444 = 3,
		Rgba5551 = 4,
		Rgb565 = 5,
		LuminanceAlpha = 6,
		LuminanceAlphaH = 7,
		Luminance = 8,
		LuminanceH = 9,
		Alpha = 10,
		AlphaH = 11,
		Depth16 = 12,
		Depth24 = 13,
		Depth16Stencil8 = 14,
		Depth24Stencil8 = 15,
		Dxt1 = 16,
		Dxt2 = 17,
		Dxt3 = 18,
		Dxt4 = 19,
		Dxt5 = 20
	};
}

#endif