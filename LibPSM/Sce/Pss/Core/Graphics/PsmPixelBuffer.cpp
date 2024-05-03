#include <Sce/Pss/Core/Graphics/PixelBuffer.hpp>
#include <Sce/Pss/Core/Graphics/PsmPixelBuffer.hpp>
#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>

#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <LibShared.hpp>

namespace Sce::Pss::Core::Graphics {
	using namespace Sce::Pss::Core::System;
	using namespace Sce::Pss::Core::Threading;
	using namespace Shared::Debug;

	int PsmPixelBuffer::Create(PixelBufferType type, int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, InternalOption option2, int* result) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetGraphicsContext() != nullptr) {
				switch (type) {
				case PixelBufferType::Texture2D:
					Logger::Error("PixelBufferType::Texture2D unimplemented.");
					return PSM_ERROR_NOT_IMPLEMENTED;
				case PixelBufferType::TextureCube:
					Logger::Error("PixelBufferType::TextureCube unimplemented.");
					return PSM_ERROR_NOT_IMPLEMENTED;
				case PixelBufferType::ColorBuffer:
					Logger::Error("PixelBufferType::TextureCube unimplemented.");
					return PSM_ERROR_NOT_IMPLEMENTED;
				case PixelBufferType::DepthBuffer:
					Logger::Error("PixelBufferType::TextureCube unimplemented.");
					return PSM_ERROR_NOT_IMPLEMENTED;
				}
			}
			else {
				return PSM_ERROR_GRAPHICS_SYSTEM;
			}
		}
		else
		{
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmPixelBuffer::Delete(int handle) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			PixelBuffer* pix = (PixelBuffer*)Handles::GetHandle(handle);
			delete pix;
		}
		else
		{
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmPixelBuffer::AddRef(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmPixelBuffer::GetInfo(int handle, PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option){
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			PixelBuffer* pixBuffer = (PixelBuffer*)Handles::GetHandle(handle);

			return pixBuffer->GetInfo(type, width, height, level, format, option);
		}
		else
		{
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}

}
