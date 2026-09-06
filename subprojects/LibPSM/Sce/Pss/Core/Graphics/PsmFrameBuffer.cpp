#include <Sce/Pss/Core/Graphics/PsmGraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/PsmFrameBuffer.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/PsmFreeList.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Graphics {

	int PsmFrameBuffer::Create(int *result){
		LOG_FUNCTION();

		if (Thread::IsMainThread()) {
			if (GraphicsContext::UniqueObjectExists())
			{
				PsmFreeList::FreeHeldObjects();
				UNIMPLEMENTED();
			}
			else {
				return PSM_ERROR_GRAPHICS_SYSTEM;
			}
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		return PSM_ERROR_NO_ERROR;
	}
	int PsmFrameBuffer::Delete(int handle){
		UNIMPLEMENTED();
	}
	int PsmFrameBuffer::AddRef(int handle){
		UNIMPLEMENTED();
	}
	int PsmFrameBuffer::SetColorTarget(int handle, int colorBuffer, int level, TextureCubeFace cubeFace, int *result){
		UNIMPLEMENTED();
	}
	int PsmFrameBuffer::SetDepthTarget(int handle, int depthBuffer, int level, TextureCubeFace cubeFace, int *result){
		UNIMPLEMENTED();
	}
}
