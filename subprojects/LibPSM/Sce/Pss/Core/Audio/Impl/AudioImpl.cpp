#define MINIAUDIO_IMPLEMENTATION // using MiniAudio for playback of audio files ...
#define MA_NO_FLAC 1 // PSM doesnt support FLAC, only mp3 and wav
#define MA_NO_ENCODING 1 // we dont need to encode audio.
#define MA_NO_GENERATION 1 // no generation of audio samples

#include <miniaudio.h>
#include <cstdint>
#include <LibShared.hpp>

#include <Sce/Pss/Core/Audio/Impl/AudioImpl.hpp>
#include <Sce/Pss/Core/Error.hpp>

using namespace Shared::Debug;
namespace Sce::Pss::Core::Audio::Impl {

	void AudioImpl::dataCallback(ma_device* device, void* output, const void* input, uint32_t frameCount) {
		AudioImpl* audioObj = reinterpret_cast<AudioImpl*>(device->pUserData);
		if (audioObj == nullptr) return;
		if (audioObj->audioDecoder == nullptr) return;

		uint64_t framesRead = 0;
		ma_decoder_read_pcm_frames(audioObj->audioDecoder.get(), output, frameCount, reinterpret_cast<ma_uint64*>(&framesRead));

		if (audioObj->Looping() && audioObj->Time() >= audioObj->LoopEnd()) {
			audioObj->SetTime(audioObj->LoopStart());
		}
	}

	uint32_t AudioImpl::calculateTotalMiliseconds() {
		uint64_t pcmFrames = 0;
		double duration = 0;

		if (this->audioDecoder != nullptr && ma_decoder_get_length_in_pcm_frames(this->audioDecoder.get(), reinterpret_cast<ma_uint64*>(&pcmFrames)) == MA_SUCCESS) {
			duration = (static_cast<double>(pcmFrames) / (static_cast<double>(this->audioDecoder->outputSampleRate) / 1000.0));
		}

		return static_cast<uint32_t>(duration);
	}
	AudioImpl::AudioImpl(std::vector<uint8_t>& buf) {
		this->audioData = buf;

		this->audioDecoder = std::make_unique<ma_decoder>();

		if (ma_decoder_init_memory(this->audioData.data(), this->audioData.size(), nullptr, this->audioDecoder.get()) == MA_SUCCESS) {
			this->audioDeviceCfg = std::make_unique<ma_device_config>();

			*this->audioDeviceCfg = ma_device_config_init(ma_device_type_playback);
			this->audioDeviceCfg->playback.format = this->audioDecoder->outputFormat;
			this->audioDeviceCfg->playback.channels = this->audioDecoder->outputChannels;
			this->audioDeviceCfg->sampleRate = this->audioDecoder->outputSampleRate;
			this->audioDeviceCfg->dataCallback = reinterpret_cast<ma_device_data_proc>(AudioImpl::dataCallback);
			this->audioDeviceCfg->pUserData = this;

			this->audioDevice = std::make_unique<ma_device>();
			if (ma_device_init(nullptr, this->audioDeviceCfg.get(), this->audioDevice.get()) != MA_SUCCESS) {
				this->SetError(PSM_ERROR_AUDIO_SYSTEM);
			}
		}
		else {
			this->SetError(PSM_ERROR_AUDIO_SYSTEM);
		}

		uint32_t duration = this->calculateTotalMiliseconds();
		this->sndLengthMilis = duration;
		this->sndLoopStart = 0;
		this->sndLoopEnd = duration;
	}

	int AudioImpl::Play() {
		this->sndPaused = false;
		if (this->audioDevice != nullptr && ma_decoder_seek_to_pcm_frame(this->audioDecoder.get(), 0) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		if (this->audioDevice != nullptr && ma_device_start(this->audioDevice.get()) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	int AudioImpl::Stop() {
		this->sndPaused = false;
		if (this->audioDevice != nullptr && ma_device_stop(this->audioDevice.get()) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		if (this->audioDecoder != nullptr && ma_decoder_seek_to_pcm_frame(this->audioDecoder.get(), 0) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	int AudioImpl::Pause() {
		this->sndPaused = true;
		if (this->audioDevice != nullptr && ma_device_stop(this->audioDevice.get()) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	int AudioImpl::Resume() {
		this->sndPaused = false;
		if (this->audioDevice != nullptr && ma_device_start(this->audioDevice.get()) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	uint32_t AudioImpl::LoopStart() {
		return this->sndLoopStart;
	}
	uint32_t AudioImpl::LoopEnd() {
		return this->sndLoopEnd;
	}

	bool AudioImpl::Paused() {
		return this->sndPaused;
	}

	bool AudioImpl::Stopped() {
		if (this->Paused()) return false;
		if (this->audioDevice == nullptr) return true;

		ma_device_state state = ma_device_get_state(this->audioDevice.get());

		return (state == ma_device_state_stopped || state == ma_device_state_stopping || state == ma_device_state_uninitialized);
	}

	bool AudioImpl::Playing() {
		if (this->Paused()) return false;
		return !this->Stopped();
	}

	bool AudioImpl::Looping() {
		return this->sndLooping;
	}
	int AudioImpl::SetLooping(bool val) {
		this->sndLooping = val;
		return PSM_ERROR_NO_ERROR;
	}

	float AudioImpl::Volume() {
		float output = 1.0f;
		if(this->audioDevice != nullptr) ma_device_get_master_volume(this->audioDevice.get(), &output);
		return output;
	}

	int AudioImpl::SetVolume(float val) {
		if (ma_device_set_master_volume(this->audioDevice.get(), val) == MA_SUCCESS) return PSM_ERROR_NO_ERROR;
		return PSM_ERROR_AUDIO_SYSTEM;
	}

	int AudioImpl::SetTime(uint32_t val) {
		uint64_t frame = static_cast<uint64_t>(static_cast<double>(val) * (static_cast<double>(this->audioDecoder->outputSampleRate) * 1000.0));
		if (this->audioDecoder != nullptr && ma_decoder_seek_to_pcm_frame(this->audioDecoder.get(), frame) == MA_SUCCESS) return PSM_ERROR_NO_ERROR;
		return PSM_ERROR_AUDIO_SYSTEM;
	}

	int AudioImpl::SetLoopStart(uint32_t val) {
		this->sndLoopStart = val;
		return PSM_ERROR_NO_ERROR;
	}
	int AudioImpl::SetLoopEnd(uint32_t val) {
		this->sndLoopEnd = val;
		return PSM_ERROR_NO_ERROR;
	}

	uint32_t AudioImpl::Duration() {
		return this->sndLengthMilis;
	}


	uint32_t AudioImpl::Time() {
		uint64_t pcmFrames = 0;
		uint32_t time = 0;
		if (this->audioDecoder != nullptr && ma_decoder_get_cursor_in_pcm_frames(this->audioDecoder.get(), reinterpret_cast<ma_uint64*>(&pcmFrames)) == MA_SUCCESS) {
			time = static_cast<uint32_t>((static_cast<double>(pcmFrames) / (static_cast<double>(this->audioDecoder->outputSampleRate) / 1000.0)));
		}
		return time;
	}

	float AudioImpl::PlaybackSpeed() {
		return this->sndPlaybackSpeed;
	}

	int AudioImpl::SetPlaybackSpeed(float val) {
		this->Pause(); 

		if (this->audioDevice != nullptr) {
			ma_device_uninit(this->audioDevice.get()); // unitalize the device 

			// change the sample rate to be sample rate * speed factor 
			this->audioDeviceCfg->sampleRate = static_cast<uint32_t>(static_cast<float>(this->audioDecoder->outputSampleRate) * static_cast<float>(val));
			this->sndPlaybackSpeed = val;

			// initalize the device again
			if(ma_device_init(nullptr, this->audioDeviceCfg.get(), this->audioDevice.get()) != MA_SUCCESS)
				return PSM_ERROR_AUDIO_SYSTEM;
		}

		this->Resume(); 
		return PSM_ERROR_NO_ERROR;
	}

	AudioImpl::~AudioImpl() {
		this->Pause();

		if(this->audioDevice != nullptr) ma_device_uninit(this->audioDevice.get());
		if(this->audioDecoder != nullptr) ma_decoder_uninit(this->audioDecoder.get());

		this->audioDevice = nullptr;
		this->audioDecoder = nullptr;
		this->audioDeviceCfg = nullptr;
		this->audioDecoderCfg = nullptr;

	}
}
