#include <Sce/PlayStation/Core/Graphics/PsmGraphicsContext.hpp>
#include <Sce/PlayStation/Core/Graphics/PsmFrameBuffer.hpp>
#include <Sce/PlayStation/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/PlayStation/Core/Error.hpp>

#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::PlayStation::Core::Graphics {
	int PsmFrameBuffer::Create(int *result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
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
