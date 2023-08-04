#include <Sce/Pss/Core/Graphics/Texture2D.hpp>
#include <glad/glad.h>
#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	Texture2D::Texture2D(std::string fileName, bool mipmap, Sce::PlayStation::Core::Graphics::PixelFormat format) {
		Logger::Debug(__FUNCTION__);
		Logger::Error("Texture2d not done yet");
	}

	Texture2D::~Texture2D() {
		Logger::Debug(__FUNCTION__);
	}

	GLenum Texture2D::GlTextureType() {
		Logger::Debug(__FUNCTION__);
		return GL_TEXTURE_2D;
	}

	int Texture2D::ActiveStateChanged(bool state) {
		Logger::Debug(__FUNCTION__);
		return PSM_ERROR_NO_ERROR;
	}

}