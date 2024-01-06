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

		if (Mix_AllocateChannels(4) < 0) {
			throw std::exception("failed to Mix_AllocateChannels.");
		}

		AudioImpl::Impl::isInitalized = true;
	}


	void* AudioImpl::OpenMP3(uint8_t* data, size_t dataSz) {
		AudioImpl::Impl::ErrorOnNotInit();

		SDL_RWops* rw = SDL_RWFromMem(data, dataSz);
		Mix_Music* mus = Mix_LoadMUS_RW(rw, true);

		return (void*)mus;
	}

	void AudioImpl::CloseMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		Mix_FreeMusic((Mix_Music*)bgmObject);
	}

	void AudioImpl::PlayMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		Mix_PlayMusic((Mix_Music*)bgmObject, 0);
	}



}