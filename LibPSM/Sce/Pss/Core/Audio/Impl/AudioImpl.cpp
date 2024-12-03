#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_FLAC // PSM doesnt support FLAC, only mp3 and wav
#include <miniaudio.h>
#include <Sce/Pss/Core/Audio/Impl/Audio.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Audio::Impl {

	void Audio::dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
		ma_decoder* decoder = (ma_decoder*)device->pUserData;
		if (decoder == nullptr) return;

		ma_decoder_read_pcm_frames(decoder, output, frameCount, nullptr);
		(void*)input;
	}

	Audio::Audio(uint8_t* buf, size_t sz) {
		this->audioData = buf;
		this->audioSz = sz;

		this->sndLooping.store(false);
		this->sndPaused.store(false);

		this->audioDecoder = new ma_decoder();

		if (ma_decoder_init_memory(this->audioData, this->audioSz, nullptr, this->audioDecoder) == MA_SUCCESS) {
			this->audioDeviceCfg = new ma_device_config();

			*this->audioDeviceCfg = ma_device_config_init(ma_device_type_playback);
			this->audioDeviceCfg->playback.format = this->audioDecoder->outputFormat;
			this->audioDeviceCfg->playback.channels = this->audioDecoder->outputChannels;
			this->audioDeviceCfg->sampleRate = this->audioDecoder->outputSampleRate;
			this->audioDeviceCfg->dataCallback = Audio::dataCallback;
			this->audioDeviceCfg->pUserData = this->audioDecoder;

			this->audioDevice = new ma_device();
			if (ma_device_init(NULL, this->audioDeviceCfg, this->audioDevice) != MA_SUCCESS) {
				this->SetError(PSM_ERROR_AUDIO_SYSTEM);
			}
		}
		else {
			this->SetError(PSM_ERROR_AUDIO_SYSTEM);
		}
	}

	int Audio::Play() {
		this->sndPaused.store(false);
		if (ma_decoder_seek_to_pcm_frame(this->audioDecoder, 0) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		if (ma_device_start(this->audioDevice) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	int Audio::Stop() {
		this->sndPaused.store(false);
		if (ma_device_stop(this->audioDevice) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		if (ma_decoder_seek_to_pcm_frame(this->audioDecoder, 0) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	int Audio::Pause() {
		this->sndPaused.store(true);
		if (ma_device_stop(this->audioDevice) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	int Audio::Resume() {
		this->sndPaused.store(false);
		if (ma_device_start(this->audioDevice) != MA_SUCCESS) return PSM_ERROR_AUDIO_SYSTEM;
		return PSM_ERROR_NO_ERROR;
	}

	
	bool Audio::Paused() {
		return this->sndPaused.load();
	}

	bool Audio::Stopped() {
		if (this->Paused()) return false;

		ma_device_state state = ma_device_get_state(this->audioDevice);

		return (state == ma_device_state_stopped || state == ma_device_state_stopping || state == ma_device_state_uninitialized);
	}

	bool Audio::Playing() {
		if (this->Paused()) return false;
		return !this->Stopped();
	}

	bool Audio::Looping() {
		return this->sndLooping.load();
	}
	void Audio::SetLooping(bool val) {
		this->sndLooping.store(val);
	}


	Audio::~Audio() {
		if(this->audioDevice != nullptr) ma_device_uninit(this->audioDevice);
		if(this->audioDecoder != nullptr) ma_decoder_uninit(this->audioDecoder);

		if(this->audioDevice != nullptr) delete this->audioDevice;
		if(this->audioDecoder != nullptr) delete this->audioDecoder;
		if(this->audioDeviceCfg != nullptr) delete this->audioDeviceCfg;
		if(this->audioDecoderCfg != nullptr) delete this->audioDecoderCfg;

		this->audioDevice = nullptr;
		this->audioDecoder = nullptr;
		this->audioDeviceCfg = nullptr;
		this->audioDecoderCfg = nullptr;

		this->audioData = nullptr; // cleaned up by callee ?
	}
}
