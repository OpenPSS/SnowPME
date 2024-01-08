#ifndef SNOW_PME_AUDIOIMPL_H
#define SNOW_PME_AUDIOIMPL_H 1
#include <iostream>
#include <mutex>
#include <Callback/Impl.hpp>
namespace SnowPME::Callback {

	class AudioImpl : public Impl{
	private:
		static int findFreeChannel();
	public:
		static const int NoChannel = -1;
		static const int TotalChannels = 100;
		static bool ChannelsUsed[TotalChannels];

		static void Init();
		static void* OpenMP3(uint8_t* data, size_t dataSz);
		static void CloseMP3(void* bgmObject);
		static bool PlayMP3(void* bgmObject, bool loop);
		static void PauseMP3(void* bgmObject);
		static void ResumeMP3(void* bgmObject);
		static void StopMP3(void* bgmObject);

		static bool IsMP3Paused(void* bgmObject);
		static bool IsMP3Playing(void* bgmObject);
		static bool IsMP3Stopped(void* bgmObject);
		
		static void SetLoop(void* bgmObject, bool loop);
	};

}

#endif