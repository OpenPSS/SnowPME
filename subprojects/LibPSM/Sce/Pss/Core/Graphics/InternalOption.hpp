#ifndef LIB_PSS_INTERNALOPTION_H
#define LIB_PSS_INTERNALOPTION_H
#include <cstdint>
#include <Sce/Pss/Core/BitwiseEnum.hpp>

namespace Sce::Pss::Core::Graphics {
	enum class InternalOption : uint32_t {
		None = 0,
		SystemResource = 1
	};

	DEFINE_BITWISE_ENUM_OPERATOR(InternalOption, uint32_t);
}

#endif