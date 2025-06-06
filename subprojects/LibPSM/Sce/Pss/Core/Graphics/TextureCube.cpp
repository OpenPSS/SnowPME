#include <Sce/Pss/Core/Graphics/TextureCube.hpp>
#include <glad/glad.h>
#include <LibShared.hpp>
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Graphics;

namespace Sce::Pss::Core::Graphics {


	TextureCube::TextureCube(std::string* fileName, bool mipmap, PixelFormat format) {
		Logger::Debug(__FUNCTION__);
		Logger::Error("TextureCube not done yet");
	}

	TextureCube::~TextureCube() {
		Logger::Debug(__FUNCTION__);
	}

	GLenum TextureCube::GlTextureType() {
		UNIMPLEMENTED();
	}

	int TextureCube::ActiveStateChanged(bool state) {
		Logger::Debug(__FUNCTION__);
		return PSM_ERROR_NO_ERROR;
	}

}