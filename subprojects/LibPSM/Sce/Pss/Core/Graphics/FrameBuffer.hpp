#ifndef LIB_PSS_FRAMEBUFFER_H
#define LIB_PSS_FRAMEBUFFER_H 1
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>

namespace Sce::Pss::Core::Graphics {

	class FrameBuffer : public GraphicsObject<FrameBuffer> {
	public:
		bool unk12 = false;
	};
}

#endif