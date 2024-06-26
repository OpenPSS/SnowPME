#ifndef LIB_PSS_PSMFRAMEBUFFER_H
#define LIB_PSS_PSMFRAMEBUFFER_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include "TextureCubeFace.hpp"


namespace Sce::Pss::Core::Graphics {
	typedef struct FrameBuffer {
		int frameBufferId;
	} FrameBuffer;

	class PsmFrameBuffer {
	public:
		static int Create(int *result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int SetColorTarget(int handle, int colorBuffer, int level, TextureCubeFace cubeFace, int *result);
		static int SetDepthTarget(int handle, int depthBuffer, int level, TextureCubeFace cubeFace, int *result);
	};
}
#endif
