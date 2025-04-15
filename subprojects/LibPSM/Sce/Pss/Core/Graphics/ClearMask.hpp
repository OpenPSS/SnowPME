#ifndef LIB_PSS_CLEARMASK_H
#define LIB_PSS_CLEARMASK_H
#include <string>
#include <Sce/Pss/Core/BitwiseEnum.hpp>

namespace Sce::Pss::Core::Graphics {
	enum class ClearMask : unsigned int {
		None = 0,
		Color = 1,
		Depth = 2,
		Stencil = 4,
		All = 7
	};

	DEFINE_BITWISE_OPERATORS(ClearMask, unsigned int);

}

#endif