#ifndef LIB_PSS_PIXELBUFFEROPTION_H
#define LIB_PSS_PIXELBUFFEROPTION_H
#include <Sce/Pss/Core/BitwiseEnum.hpp>
#include <cstdint>

namespace Sce::Pss::Core::Graphics {
	enum class PixelBufferOption : uint32_t {
		None = 0,
		Renderable = 1
	};
	DEFINE_BITWISE_ENUM_OPERATOR(PixelBufferOption, uint32_t);
}

#endif