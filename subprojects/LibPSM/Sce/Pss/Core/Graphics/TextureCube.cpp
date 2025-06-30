#include <Sce/Pss/Core/Graphics/TextureCube.hpp>
#include <glad/glad.h>
#include <LibShared.hpp>
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Graphics;

namespace Sce::Pss::Core::Graphics {


	TextureCube::TextureCube(std::string& fileName, bool mipmap, PixelFormat format) {
		LOG_FUNCTION();
		UNIMPLEMENTED_ERRORABLE("TextureCube");
	}

	TextureCube::~TextureCube() {
		LOG_FUNCTION();
	}

	GLenum TextureCube::GLTextureType() {
		UNIMPLEMENTED();
	}

	int TextureCube::ActiveStateChanged(bool state) {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

}