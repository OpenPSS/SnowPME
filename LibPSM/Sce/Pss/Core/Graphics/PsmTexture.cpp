#include <Sce/Pss/Core/Graphics/PsmTexture.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Mono/Util.hpp>
#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <Sce/Pss/Core/Graphics/TextureCube.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <LibShared.hpp>
#include <mono/mono.h>


namespace Sce::Pss::Core::Graphics {
	using namespace Sce::Pss::Core;
	using namespace Sce::Pss::Core::System;
	using namespace Sce::Pss::Core::Threading;
	using namespace Sce::Pss::Core::Graphics;

	using namespace Shared::Debug;

	int PsmTexture::FromFile(PixelBufferType type, MonoString* fileName, bool mipmap, PixelFormat format, int* result) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetGraphicsContext() == nullptr)
				return PSM_ERROR_GRAPHICS_SYSTEM;
			
			std::string filename;
			Mono::Util::MonoStringToStdString(fileName, filename);

			Texture* tex = nullptr;
			if (type == PixelBufferType::Texture2D) {
				Logger::Debug("type is PixelBufferType::Texture2D");
				tex = new Texture2D(&filename, mipmap, format);
				ReturnErrorable(tex);
			}
			else if(type == PixelBufferType::TextureCube) {
				Logger::Debug("type is PixelBufferType::TextureCube");
				tex = new TextureCube(&filename, mipmap, format);
				ReturnErrorable(tex);
			}
			
			if (tex != nullptr) {
				*result = Handles::CreateHandle((uintptr_t)tex);
				return PSM_ERROR_NO_ERROR;
			}
			return PSM_ERROR_INVALID_PARAMETER;

		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		return PSM_ERROR_NO_ERROR;
	}
	int PsmTexture::FromImage(PixelBufferType type, MonoArray* fileImage, bool mipmap, PixelFormat format, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetFilter(int handle, TextureFilter* filter) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetWrap(int handle, TextureWrap* filter) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetMaxAnisotropy(int handle, float anisotropy) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::SetPixels(int handle, int level, TextureCubeFace cubeFace, int* pixels, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmTexture::GenerateMipmap(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
