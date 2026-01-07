#ifndef LIB_PSS_PIXELFORMATS_H
#define LIB_PSS_PIXELFORMATS_H 1
#include <cstdint>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>

#define SIZE_CHK(type, size) static_assert(sizeof(type) == size, "sizeof(" #type ") is not " #size " bytes")

namespace Sce::Pss::Core::Graphics::PixelFormats {
	typedef uint16_t half;
	typedef int8_t byte;
	typedef uint8_t ubyte;

	typedef PACK(struct {
#ifdef _MSC_VER
		uint16_t val : 24; // what the fuck is msvc; this is the only way i found to make this work; it doesnt work as a uint32_t.
#else
		uint32_t val : 24; // very sane, good compiler ... 
#endif
	}) uint24_t;
	SIZE_CHK(uint24_t, 3);


	typedef PACK(struct Rgba {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	}) Rgba;
	SIZE_CHK(Rgba, 4);

	typedef PACK(struct RgbaH {
		half r;
		half g;
		half b;
		half a;
	}) RgbaH;
	SIZE_CHK(RgbaH, 8);

	typedef PACK(struct Rgba4444 {
		uint16_t r : 4;
		uint16_t g : 4;
		uint16_t b : 4;
		uint16_t a : 4;
	}) Rgba4444;
	SIZE_CHK(Rgba4444, 2);

	typedef PACK(struct Rgba5551 {
		uint16_t r : 5;
		uint16_t g : 5;
		uint16_t b : 5;
		uint16_t a : 1;
	}) Rgba5551;
	SIZE_CHK(Rgba5551, 2);

	typedef PACK(struct Rgb565 {
		uint16_t r : 5;
		uint16_t g : 6;
		uint16_t b : 5;
	}) Rgb565;
	SIZE_CHK(Rgb565, 2);

	typedef PACK(struct LuminanceAlpha {
		uint8_t l;
		uint8_t a;
	}) LuminanceAlpha;
	SIZE_CHK(LuminanceAlpha, 2);

	typedef PACK(struct LuminanceAlphaH {
		half l;
		half a;
	}) LuminanceAlphaH;
	SIZE_CHK(LuminanceAlphaH, 4);

	typedef PACK(struct Luminance {
		byte l;
	}) Luminance;
	SIZE_CHK(Luminance, 1);

	typedef PACK(struct LuminanceH {
		half l;
	}) LuminanceH;
	SIZE_CHK(LuminanceH, 2);

	typedef PACK(struct Alpha {
		byte a;
	}) Alpha;
	SIZE_CHK(Alpha, 1);

	typedef PACK(struct AlphaH {
		half a;
	}) AlphaH;
	SIZE_CHK(AlphaH, 2);

	typedef PACK(struct Depth16 {
		uint16_t d;
	}) Depth16;
	SIZE_CHK(Depth16, 2);

	typedef PACK(struct Depth24 {
		uint24_t d;
		uint8_t pad;
	}) Depth24;
	SIZE_CHK(Depth24, 4);

	typedef PACK(struct Depth16Stencil8 {
		uint16_t d;
		uint8_t s;
		uint8_t pad;
	}) Depth16Stencil8;
	SIZE_CHK(Depth16Stencil8, 4);


	typedef PACK(struct Depth24Stencil8 {
		uint24_t d;
		uint8_t s;
	}) Depth24Stencil8;
	SIZE_CHK(Depth24Stencil8, 4);

	#define Dxt1_Size 4;
	#define Dxt2_Size 8;
	#define Dxt3_Size 8;
	#define Dxt4_Size 8;
	#define Dxt5_Size 8;

}


#endif