#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <glad/glad.h>
#include <LibShared.hpp>


namespace Sce::Pss::Core::Graphics {
	using namespace Shared::Debug;

	Texture::Texture() {

	}

	Texture::~Texture() {

	}

	int Texture::ActiveStateChanged(bool state) {
		Logger::Debug(__FUNCTION__);
		return PSM_ERROR_NO_ERROR;
	}

}