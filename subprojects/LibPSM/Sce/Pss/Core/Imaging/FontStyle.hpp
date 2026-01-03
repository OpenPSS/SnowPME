#ifndef LIB_PSS_FONTSTYLE_H
#define LIB_PSS_FONTSTYLE_H
#include <Sce/Pss/Core/BitwiseEnum.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Imaging {
	enum class FontStyle : uint32_t {
		Regular = 0,
		Bold = 1,
		Italic = 2
	};

	DEFINE_BITWISE_ENUM_OPERATOR(FontStyle, uint32_t);
}

#endif