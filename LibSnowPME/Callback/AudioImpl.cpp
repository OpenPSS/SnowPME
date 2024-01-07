#include <Callback/AudioImpl.hpp>
#include <Callback/AudioObject.hpp>

#include <sdl/SDL.h>
#include <sdl/SDL_mixer.h>
#include <exception>
#include <mutex>

namespace SnowPME::Callback {

	bool AudioImpl::ChannelsUsed[AudioImpl::TotalChannels];
	
	void AudioImpl::Init() {
		if (Mix_Init(MIX_INIT_MP3) < 0) {
			throw std::exception("failed to Mix_Init.");
		}

		if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) < 0) {
			throw std::exception("failed to Mix_OpenAudio.");
		}

		if (Mix_AllocateChannels(AudioImpl::TotalChannels) < 0) {
			throw std::exception("failed to Mix_AllocateChannels.");
		}

		memset(AudioImpl::ChannelsUsed, false, AudioImpl::TotalChannels);

		AudioImpl::Impl::isInitalized = true;
	}


	int AudioImpl::findFreeChannel() {
		for (int i = 0; i < AudioImpl::TotalChannels; i++) {
			if (AudioImpl::ChannelsUsed[i] == false) {
				return i;
			}
		}
		return AudioImpl::NoChannel;
	}

	void* AudioImpl::OpenMP3(uint8_t* data, size_t dataSz) {
		AudioImpl::Impl::ErrorOnNotInit();

		SDL_RWops* rw = SDL_RWFromMem(data, dataSz);
		Mix_Chunk* mus = Mix_LoadWAV_RW(rw, true);

		AudioObject* audioObject = new AudioObject();
		audioObject->channeNumber = AudioImpl::NoChannel;
		audioObject->audioObject = mus;

		return (void*)audioObject;
	}

	void AudioImpl::CloseMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;

		Mix_FreeChunk(audioObject->audioObject);
		AudioImpl::ChannelsUsed[audioObject->channeNumber] = false;

		delete audioObject;
	}

	bool AudioImpl::PlayMP3(void* bgmObject, bool loop) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return false;
		
		int useChannel = findFreeChannel();
		if (useChannel == AudioImpl::NoChannel) return false;

		AudioObject* audioObject = (AudioObject*)bgmObject;
		
		if (Mix_PlayChannel(useChannel, audioObject->audioObject, loop) >= 0) {
			audioObject->channeNumber = useChannel;
			AudioImpl::ChannelsUsed[useChannel] = true;

			return true;
		}

		return false;
	}
	void AudioImpl::PauseMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;

		if (!Mix_Paused(audioObject->channeNumber))
			Mix_Pause(audioObject->channeNumber);
	}

	void AudioImpl::ResumeMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;
		
		AudioObject* audioObject = (AudioObject*)bgmObject;

		if (Mix_Paused(audioObject->channeNumber))
			Mix_Resume(audioObject->channeNumber);
	}

	void AudioImpl::SetLoop(void* bgmObject, bool loop) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;
		// TODO: work out how to set it to loop while its playing already
		
		throw std::exception("Not implemented.");


	}



}