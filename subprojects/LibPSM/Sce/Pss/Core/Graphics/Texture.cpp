#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <glad/glad.h>
#include <LibShared.hpp>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	Texture::Texture() {

	}

	int Texture::ActiveStateChanged(bool state) {
		LOG_FUNCTION();
		return PSM_ERROR_NO_ERROR;
	}

}