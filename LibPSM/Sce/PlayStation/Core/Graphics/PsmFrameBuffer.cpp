#include "PsmFrameBuffer.hpp"
#include "TextureCubeFace.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmFrameBuffer::Create(int *result){
		std::cout << "Sce::PlayStation::Core::Graphics::Create(int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmFrameBuffer::Delete(int handle){
		std::cout << "Sce::PlayStation::Core::Graphics::Delete(int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmFrameBuffer::AddRef(int handle){
		std::cout << "Sce::PlayStation::Core::Graphics::AddRef(int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmFrameBuffer::SetColorTarget(int handle, int colorBuffer, int level, TextureCubeFace cubeFace, int *result){
		std::cout << "Sce::PlayStation::Core::Graphics::SetColorTarget(int, int, int, Sce::PlayStation::Core::Graphics::TextureCubeFace, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmFrameBuffer::SetDepthTarget(int handle, int depthBuffer, int level, TextureCubeFace cubeFace, int *result){
		std::cout << "Sce::PlayStation::Core::Graphics::SetDepthTarget(int, int, int, Sce::PlayStation::Core::Graphics::TextureCubeFace, int *) Unimplemented." << std::endl;
		return 0;
	}
}
