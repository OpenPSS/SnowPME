#include <Sce/Pss/Core/Graphics/PsmGraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/PsmFrameBuffer.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	int PsmFrameBuffer::Create(int *result){
		Unimplemented();
	}
	int PsmFrameBuffer::Delete(int handle){
		Unimplemented();
	}
	int PsmFrameBuffer::AddRef(int handle){
		Unimplemented();
	}
	int PsmFrameBuffer::SetColorTarget(int handle, int colorBuffer, int level, TextureCubeFace cubeFace, int *result){
		Unimplemented();
	}
	int PsmFrameBuffer::SetDepthTarget(int handle, int depthBuffer, int level, TextureCubeFace cubeFace, int *result){
		Unimplemented();
	}
}
