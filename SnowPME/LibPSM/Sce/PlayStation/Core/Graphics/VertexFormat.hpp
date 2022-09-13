#ifndef LIB_PSM_VERTEXFORMAT_H
#define LIB_PSM_VERTEXFORMAT_H 1
namespace Sce::PlayStation::Core::Graphics {
	enum class VertexFormat : unsigned int {
		None = 0,
		Float = 0x100,
		Float2 = 257,
		Float3 = 258,
		Float4 = 259,
		Half = 0x200,
		Half2 = 513,
		Half3 = 514,
		Half4 = 515,
		Short = 1536,
		Short2 = 1537,
		Short3 = 1538,
		Short4 = 1539,
		UShort = 1792,
		UShort2 = 1793,
		UShort3 = 1794,
		UShort4 = 1795,
		Byte = 0x800,
		Byte2 = 2049,
		Byte3 = 2050,
		Byte4 = 2051,
		UByte = 2304,
		UByte2 = 2305,
		UByte3 = 2306,
		UByte4 = 2307,
		ShortN = 5632,
		Short2N = 5633,
		Short3N = 5634,
		Short4N = 5635,
		UShortN = 5888,
		UShort2N = 5889,
		UShort3N = 5890,
		UShort4N = 5891,
		ByteN = 6144,
		Byte2N = 6145,
		Byte3N = 6146,
		Byte4N = 6147,
		UByteN = 6400,
		UByte2N = 6401,
		UByte3N = 6402,
		UByte4N = 6403
	};
}

#endif