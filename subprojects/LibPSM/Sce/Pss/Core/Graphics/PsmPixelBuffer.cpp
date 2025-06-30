#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Graphics/PsmPixelBuffer.hpp>
#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>

#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <LibShared.hpp>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Threading;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {


	int PsmPixelBuffer::Create(PixelBufferType type, int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption option2, int* result) {
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			if (GraphicsContext::UniqueObject() != nullptr) {
				switch (type) {
				case PixelBufferType::Texture2D:
					UNIMPLEMENTED_MSG("PixelBufferType::Texture2D");
				case PixelBufferType::TextureCube:
					UNIMPLEMENTED_MSG("PixelBufferType::TextureCube");
				case PixelBufferType::ColorBuffer:
					UNIMPLEMENTED_MSG("PixelBufferType::ColorBuffer");
				case PixelBufferType::DepthBuffer:
					UNIMPLEMENTED_MSG("PixelBufferType::DepthBuffer");
				}
				return PSM_ERROR_COMMON_ARGUMENT;
			}
			else {
				return PSM_ERROR_GRAPHICS_SYSTEM;
			}
		}
		else
		{
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmPixelBuffer::Delete(int handle) {
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			if (!Handles<PixelBuffer>::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			std::shared_ptr<PixelBuffer> pix = Handles<PixelBuffer>::Get(handle);
			PixelBuffer::Delete(pix);

			return PSM_ERROR_NO_ERROR;
		}
		else
		{
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmPixelBuffer::AddRef(int handle) {
		UNIMPLEMENTED();
	}
	int PsmPixelBuffer::GetInfo(int handle, PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option){
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			if (!Handles<PixelBuffer>::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			std::shared_ptr<PixelBuffer> pixBuffer = Handles<PixelBuffer>::Get(handle);

			return pixBuffer->GetInfo(type, width, height, level, format, option);
		}
		else
		{
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}

}
