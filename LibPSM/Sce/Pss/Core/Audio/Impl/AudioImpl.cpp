#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_FLAC // PSM doesnt support FLAC, only mp3 and wav
#include <miniaudio.h>
#include <Sce/Pss/Core/Audio/Impl/Audio.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Audio::Impl {

	void Audio::dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
		Impl::Audio* audioObj = (Impl::Audio*)device->pUserData;
		if (audioObj == nullptr) return;
		if (audioObj->audioDecoder == nullptr) return;

		uint64_t framesRead = 0;
		ma_decoder_read_pcm_frames(audioObj->audioDecoder, output, frameCount, &framesRead);

		if (audioObj->Looping() && audioObj->Time() >= audioObj->LoopEnd()) {
			audioObj->SetTime(audioObj->LoopStart());
		}
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
			this->audioDeviceCfg->pUserData = this;
			ma_context ctx;

			this->audioDevice = new ma_device();
			if (ma_device_init(NULL, this->audioDeviceCfg, this->audioDevice) != MA_SUCCESS) {
				this->SetError(PSM_ERROR_AUDIO_SYSTEM);
			}
		}
		else {
			this->SetError(PSM_ERROR_AUDIO_SYSTEM);
		}

		this->sndLoopStart.store(0);
		this->sndLoopEnd.store(this->Duration());
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

	uint64_t Audio::LoopStart() {
		return this->sndLoopStart.load();
	}
	uint64_t Audio::LoopEnd() {
		return this->sndLoopEnd.load();
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
	int Audio::SetLooping(bool val) {
		this->sndLooping.store(val);
		return PSM_ERROR_NO_ERROR;
	}

	float Audio::Volume() {
		float output = 1.0f;
		ma_device_get_master_volume(this->audioDevice, &output);
		return output;
	}

	int Audio::SetVolume(float val) {
		if (ma_device_set_master_volume(this->audioDevice, val) == MA_SUCCESS) return PSM_ERROR_NO_ERROR;
		return PSM_ERROR_AUDIO_SYSTEM;
	}

	int Audio::SetTime(uint64_t val) {
		uint64_t frame = (uint64_t)((double)val * ((double)this->audioDecoder->outputSampleRate * (double)1000.0));
		if (ma_decoder_seek_to_pcm_frame(this->audioDecoder, frame) == MA_SUCCESS) return PSM_ERROR_NO_ERROR;
		return PSM_ERROR_AUDIO_SYSTEM;
	}

	int Audio::SetLoopStart(uint64_t val) {
		this->sndLoopStart.store(val);
		return PSM_ERROR_NO_ERROR;
	}
	int Audio::SetLoopEnd(uint64_t val) {
		this->sndLoopEnd.store(val);
		return PSM_ERROR_NO_ERROR;
	}

	uint64_t Audio::Duration() {
		uint64_t pcmFrames = 0;
		uint64_t duration = 0;

		if (ma_decoder_get_length_in_pcm_frames(this->audioDecoder, &pcmFrames) == MA_SUCCESS) {
			duration = (uint64_t)(((double)pcmFrames / ((double)this->audioDecoder->outputSampleRate / (double)1000.0)));
		}
		return duration;
	}

	uint64_t Audio::Time() {
		uint64_t pcmFrames = 0;
		uint64_t time = 0;
		if (ma_decoder_get_cursor_in_pcm_frames(this->audioDecoder, &pcmFrames) == MA_SUCCESS) {
			time = (uint64_t)(((double)pcmFrames / ((double)this->audioDecoder->outputSampleRate / (double)1000.0)));
		}
		return time;
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

	}
}
