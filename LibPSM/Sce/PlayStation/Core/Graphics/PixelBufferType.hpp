#ifndef LIB_PSM_PIXELBUFFERTYPE_H
#define LIB_PSM_PIXELBUFFERTYPE_H

namespace Sce::PlayStation::Core::Graphics {
	enum class PixelBufferType : unsigned int {
		None = 0,
		Texture2D = 1,
		TextureCube = 2,
		ColorBuffer = 3,
		DepthBuffer = 4
	};
}

#endif