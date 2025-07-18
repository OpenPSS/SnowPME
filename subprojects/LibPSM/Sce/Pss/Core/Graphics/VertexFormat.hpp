#ifndef LIB_PSS_VERTEXFORMAT_H
#define LIB_PSS_VERTEXFORMAT_H 1
#include <Sce/Pss/Core/BitwiseEnum.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Graphics {

	enum class VertexFormat : uint32_t {
		None = 0x0,
		Float = 0x100,
		Float2 = 0x101,
		Float3 = 0x102,
		Float4 = 0x103,
		Half = 0x200,
		Half2 = 0x201,
		Half3 = 0x202,
		Half4 = 0x203,
		Short = 0x600,
		Short2 = 0x601,
		Short3 = 0x602,
		Short4 = 0x603,
		UShort = 0x700,
		UShort2 = 0x701,
		UShort3 = 0x702,
		UShort4 = 0x703,
		Byte = 0x800,
		Byte2 = 0x801,
		Byte3 = 0x802,
		Byte4 = 0x803,
		UByte = 0x900,
		UByte2 = 0x901,
		UByte3 = 0x902,
		UByte4 = 0x903,
		ShortN = 0x1600,
		Short2N = 0x1601,
		Short3N = 0x1602,
		Short4N = 0x1603,
		UShortN = 0x1700,
		UShort2N = 0x1701,
		UShort3N = 0x1702,
		UShort4N = 0x1703,
		ByteN = 0x1800,
		Byte2N = 0x1801,
		Byte3N = 0x1802,
		Byte4N = 0x1803,
		UByteN = 0x1900,
		UByte2N = 0x1901,
		UByte3N = 0x1902,
		UByte4N = 0x1903
	};

	DEFINE_BITWISE_ENUM_OPERATOR(VertexFormat, uint32_t)
}

#endif