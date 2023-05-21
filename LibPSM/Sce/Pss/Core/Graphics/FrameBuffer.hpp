#ifndef LIB_PSM_FRAMEBUFFER_H
#define LIB_PSM_FRAMEBUFFER_H 1
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>

namespace Sce::Pss::Core::Graphics {

	class FrameBuffer : public GraphicsObject {
	public:
		int ActiveStateChanged(bool state);
		FrameBuffer();
		~FrameBuffer();
	};
}

#endif