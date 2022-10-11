#include "PsmGraphicsContext.hpp"
#include "PsmFrameBuffer.hpp"
#include "TextureCubeFace.hpp"
#include "../Error.hpp"
#include <LibSnowPME.hpp>
using namespace SnowPME::Debug;

namespace Sce::PlayStation::Core::Graphics {
	int PsmFrameBuffer::Create(int *result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;

		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			if (CTX_CHECK) return PSM_ERROR_GRAPHICS_SYSTEM;
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmFrameBuffer::Delete(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmFrameBuffer::AddRef(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmFrameBuffer::SetColorTarget(int handle, int colorBuffer, int level, TextureCubeFace cubeFace, int *result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmFrameBuffer::SetDepthTarget(int handle, int depthBuffer, int level, TextureCubeFace cubeFace, int *result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
