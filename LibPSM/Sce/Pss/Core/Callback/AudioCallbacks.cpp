#include <Sce/Pss/Core/Callback/AudioCallbacks.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Callback {

	bool AudioCallbacks::isInitalized = false;

	void*   (*AudioCallbacks::openMp3)(uint8_t* data, size_t dataSz) = nullptr;
	void	(*AudioCallbacks::closeMp3)(void* bgmObject) = nullptr;
	void	(*AudioCallbacks::playMp3)(void* bgmObject) = nullptr;


	void AudioCallbacks::Init(void* (*openMp3)(uint8_t*, size_t),
							  void  (*closeMp3)(void* bgmObject),
						      void  (*playMp3)(void* bgmObject)) {
		AudioCallbacks::openMp3 = openMp3;
		AudioCallbacks::closeMp3 = closeMp3;
		AudioCallbacks::playMp3 = playMp3;
		AudioCallbacks::isInitalized = true;
	}
	
	void AudioCallbacks::CloseMP3(void* bgmObject) {
		if (AudioCallbacks::isInitalized) {
			closeMp3(bgmObject);
		}
		else {
			throw std::exception("AudioCallbacks is not initalized,");
		}
	}

	void AudioCallbacks::PlayMP3(void* bgmObject) {
		if (AudioCallbacks::isInitalized) {
			return playMp3(bgmObject);
		}
		else {
			throw std::exception("AudioCallbacks is not initalized,");
		}
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