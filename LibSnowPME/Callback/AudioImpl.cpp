#include <Callback/AudioImpl.hpp>
#include <Callback/AudioObject.hpp>

#include <SDL.h>
#include <SDL_mixer.h>
#include <exception>
#include <mutex>
#include <cstring>
#include <LibShared.hpp>

using namespace Shared::Debug;

namespace SnowPME::Callback {

	bool AudioImpl::ChannelsUsed[AudioImpl::TotalChannels];
	
	void AudioImpl::Init() {
		if (Mix_Init(MIX_INIT_MP3) < 0) {
			throw std::runtime_error("failed to Mix_Init.");
		}

		if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) >= 0) {
			Logger::Warn("failed to Mix_OpenAudio.");

			if (Mix_AllocateChannels(AudioImpl::TotalChannels) < 0) {
				throw std::runtime_error("failed to Mix_AllocateChannels.");
			}

			std::memset(AudioImpl::ChannelsUsed, false, AudioImpl::TotalChannels);

			AudioImpl::Impl::isInitalized = true;
		}
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
		audioObject->channelNumber = AudioImpl::NoChannel;
		audioObject->audioObject = mus;

		return (void*)audioObject;
	}

	void AudioImpl::CloseMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;

		Mix_FreeChunk(audioObject->audioObject);
		AudioImpl::ChannelsUsed[audioObject->channelNumber] = false;
		audioObject->channelNumber = AudioImpl::NoChannel;

		delete audioObject;
	}

	bool AudioImpl::PlayMP3(void* bgmObject, bool loop) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return false;
		
		int useChannel = findFreeChannel();
		if (useChannel == AudioImpl::NoChannel) return false;

		AudioObject* audioObject = (AudioObject*)bgmObject;
		
		if (Mix_PlayChannel(useChannel, audioObject->audioObject, loop) >= 0) {
			audioObject->channelNumber = useChannel;
			AudioImpl::ChannelsUsed[useChannel] = true;

			return true;
		}

		return false;
	}
	void AudioImpl::PauseMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;

		if (AudioImpl::IsMP3Playing(audioObject)) {
			Mix_Pause(audioObject->channelNumber);
		}
	}

	void AudioImpl::ResumeMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;

		if (AudioImpl::IsMP3Paused(audioObject)) {
			Mix_Resume(audioObject->channelNumber);
		}
	}

	void AudioImpl::StopMP3(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;
		Mix_HaltChannel(audioObject->channelNumber);
		AudioImpl::ChannelsUsed[audioObject->channelNumber] = false;
		audioObject->channelNumber = AudioImpl::NoChannel;
	}

	void AudioImpl::SetLoop(void* bgmObject, bool loop) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return;

		AudioObject* audioObject = (AudioObject*)bgmObject;
		// TODO: work out how to set it to loop while its playing already


		throw std::runtime_error("Not implemented.");
	}

	bool AudioImpl::IsMP3Paused(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return false;

		AudioObject* audioObject = (AudioObject*)bgmObject;

		if (audioObject->channelNumber != AudioImpl::NoChannel)
			return Mix_Paused(audioObject->channelNumber);
		else
			return false;

	}
	bool AudioImpl::IsMP3Playing(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return false;

		AudioObject* audioObject = (AudioObject*)bgmObject;

		if (audioObject->channelNumber != AudioImpl::NoChannel)
			return Mix_Playing(audioObject->channelNumber);
		else
			return false;
	}
	bool AudioImpl::IsMP3Stopped(void* bgmObject) {
		AudioImpl::Impl::ErrorOnNotInit();
		if (bgmObject == nullptr) return false;

		AudioObject* audioObject = (AudioObject*)bgmObject;
		return (audioObject->channelNumber == AudioImpl::NoChannel);

	}

}
