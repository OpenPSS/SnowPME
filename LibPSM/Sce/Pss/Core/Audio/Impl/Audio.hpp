#ifndef LIB_PSS_IMPL_AUDIO_H
#define LIB_PSS_IMPL_AUDIO_H 1
#define MA_NO_FLAC // PSM doesnt support FLAC, only mp3 and wav
#include <miniaudio.h>
#include <Sce/Pss/Core/Errorable.hpp>
#include <cstdint>
#include <atomic>

namespace Sce::Pss::Core::Audio::Impl {
	class Audio : public Errorable {
	private:
		ma_device_config* audioDeviceCfg = nullptr;
		ma_device* audioDevice = nullptr;
		ma_decoder* audioDecoder = nullptr;
		ma_decoder_config* audioDecoderCfg = nullptr;
		
		uint8_t* audioData = nullptr;
		size_t audioSz = 0;

		std::atomic<bool> sndPaused;
		std::atomic<bool> sndLooping;

		static void dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);
	public:
		Audio(uint8_t* buf, size_t sz);
		int Play();
		int Stop();
		int Pause();
		int Resume();

		bool Paused();
		bool Stopped();
		bool Playing();

		bool Looping();
		void SetLooping(bool val);

		~Audio();
	};
};

#endif