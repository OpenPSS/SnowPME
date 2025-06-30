#include <Sce/Pss/Core/Graphics/PsmTexture.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <Sce/Pss/Core/Graphics/TextureCube.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <LibShared.hpp>

#include <mono/mono.h>

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Mono;

using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {


	int PsmTexture::FromFile(PixelBufferType type, MonoString* fileName, bool mipmap, PixelFormat format, int* result) {
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			if (GraphicsContext::UniqueObject() == nullptr)
				return PSM_ERROR_GRAPHICS_SYSTEM;
			
			std::string filename;
			MonoUtil::MonoStringToStdString(fileName, filename);

			if (type == PixelBufferType::Texture2D) {
				Logger::Debug("type is PixelBufferType::Texture2D");
				std::shared_ptr<Texture2D> tex = Texture2D::Create(filename, mipmap, format);
				RETURN_ERRORABLE_PSMOBJECT(tex, Texture2D);
				*result = tex->Handle();
				return PSM_ERROR_NO_ERROR;
			}
			else if(type == PixelBufferType::TextureCube) {
				Logger::Debug("type is PixelBufferType::TextureCube");
				std::shared_ptr<TextureCube> tex = TextureCube::Create(filename, mipmap, format);
				RETURN_ERRORABLE_PSMOBJECT(tex, TextureCube);
				*result = tex->Handle();
				return PSM_ERROR_NO_ERROR;
			}
			

			return PSM_ERROR_INVALID_PARAMETER;

		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		return PSM_ERROR_NO_ERROR;
	}
	int PsmTexture::FromImage(PixelBufferType type, MonoArray* fileImage, bool mipmap, PixelFormat format, int* result) {
		UNIMPLEMENTED();
	}
	int PsmTexture::SetFilter(int handle, TextureFilter* filter) {
		UNIMPLEMENTED();
	}
	int PsmTexture::SetWrap(int handle, TextureWrap* filter) {
		UNIMPLEMENTED();
	}
	int PsmTexture::SetMaxAnisotropy(int handle, float anisotropy) {
		UNIMPLEMENTED();
	}
	int PsmTexture::SetPixels(int handle, int level, TextureCubeFace cubeFace, int* pixels, PixelFormat format, int offset, int pitch, int dx, int dy, int dw, int dh) {
		UNIMPLEMENTED();
	}
	int PsmTexture::GenerateMipmap(int handle) {
		UNIMPLEMENTED();
	}
}
