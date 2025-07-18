#ifndef LIB_PSS_IMPL_MODE_IMAGE_H
#define LIB_PSS_IMPL_MODE_IMAGE_H 1
#include <cstdint>
#include <Sce/Pss/Core/BitwiseEnum.hpp>

namespace Sce::Pss::Core::Imaging::Impl {
	enum class ImageImplMode : uint32_t {
		Rgba = 4,
		A = 14
	};

	DEFINE_BITWISE_ENUM_OPERATOR(ImageImplMode, uint32_t);
}

#endif