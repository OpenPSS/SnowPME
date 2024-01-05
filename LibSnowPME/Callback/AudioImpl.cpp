#include <Callback/AudioImpl.hpp>
#include <sdl/SDL.h>
#include <sdl/SDL_mixer.h>


namespace SnowPME::Callback {

	void AudioImpl::Init() {
		if (Mix_Init(MIX_INIT_MP3) < 0) {
			throw std::exception("failed to Mix_Init.");
		}

		if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) < 0) {
			throw std::exception("failed to Mix_OpenAudio.");
		}

		if (Mix_AllocateChannels(5)) {
			throw std::exception("failed to Mix_AllocateChannels.");
		}

		AudioImpl::isInitalized = true;
	}
	void* AudioImpl::OpenMP3(uint8_t* data, size_t dataSz) {
		AudioImpl::ErrorOnNotInit();
		return nullptr;
	}

}