#ifndef LIB_PSS_IMPL_AUDIO_H
#define LIB_PSS_IMPL_AUDIO_H 1

#include <Sce/Pss/Core/Errorable.hpp>

#include <miniaudio.h>
#include <cstdint>
#include <atomic>
#include <memory>

namespace Sce::Pss::Core::Audio::Impl {
	class AudioImpl : public Errorable {
	private:
		std::unique_ptr<ma_device_config> audioDeviceCfg = nullptr;
		std::unique_ptr<ma_device> audioDevice = nullptr;
		std::unique_ptr<ma_decoder> audioDecoder = nullptr;
		std::unique_ptr<ma_decoder_config> audioDecoderCfg = nullptr;
		std::vector<uint8_t> audioData;

		std::atomic<bool> sndPaused = false;
		std::atomic<bool> sndLooping = false;
		
		std::atomic<float> sndPlaybackSpeed = 1.0f;

		std::atomic<uint32_t> sndLoopStart = 0;
		std::atomic<uint32_t> sndLoopEnd = -1;;

		static void dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);
	public:
		AudioImpl(std::vector<uint8_t>& buf);
		~AudioImpl();

		int Play();
		int Stop();
		int Pause();
		int Resume();

		bool Paused();
		bool Stopped();
		bool Playing();
		
		float Volume();
		int SetVolume(float val);

		uint32_t LoopStart();
		uint32_t LoopEnd();
		int SetLoopStart(uint32_t val);
		int SetLoopEnd(uint32_t val);

		float PlaybackSpeed();
		int SetPlaybackSpeed(float val);

		uint32_t Time();
		int SetTime(uint32_t val);
		uint32_t Duration();

		bool Looping();
		int SetLooping(bool val);
	};
};

#endif