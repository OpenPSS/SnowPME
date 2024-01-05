#include <Sce/Pss/Core/Callback/AudioCallbacks.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Callback {

	bool AudioCallbacks::isInitalized = false;

	void*   (*AudioCallbacks::openMp3)(uint8_t* data, size_t dataSz) = nullptr;

	void AudioCallbacks::Init(void* (*openMp3)(uint8_t* data, size_t dataSz)) {
		AudioCallbacks::openMp3 = openMp3;
		AudioCallbacks::isInitalized = true;
	}

	void* AudioCallbacks::OpenMP3(uint8_t* data, size_t dataSz) {
		if (AudioCallbacks::isInitalized) {
			return openMp3(data, dataSz);
		}
		else {
			throw std::exception("AudioCallbacks is not initalized,");
		}
	}
}