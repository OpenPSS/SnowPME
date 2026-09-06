#ifndef LIB_PSS_PSMOBJECT_TYPE_H
#define LIB_PSS_PSMOBJECT_TYPE_H 1
#include <Sce/Pss/Core/BitwiseEnum.hpp>

namespace Sce::Pss::Core::Graphics {
	enum class PsmObjectType : uint32_t {
		GraphicsContext = 0,
		Shader = 1,
		VertexBuffer = 2,
		Texture = 3,
		FrameBuffer = 4
	};

	DEFINE_BITWISE_ENUM_OPERATOR(PsmObjectType, uint32_t);
}

#endif