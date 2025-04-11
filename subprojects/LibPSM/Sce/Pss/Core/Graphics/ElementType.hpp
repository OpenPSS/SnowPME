#ifndef LIB_PSS_ELEMENTTYPE_H
#define LIB_PSS_ELEMENTTYPE_H 1
namespace Sce::Pss::Core::Graphics {
	enum class ElementType : unsigned int {
		None = 0x0,
		Float = 0x100,
		Half = 0x200,
		Short = 0x600,
		UShort = 0x700,
		Byte = 0x800,
		UByte = 0x900
	};
}
#endif