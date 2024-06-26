#ifndef LIB_PSS_SOUNDPLAYER_H
#define LIB_PSS_SOUNDPLAYER_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include <Sce/Pss/Core/Audio/SoundStatus.hpp>


namespace Sce::Pss::Core::Audio {
	class SoundPlayer {
	public:
		static int ReleaseNative(int handle);
		static int PlayNative(int handle);
		static int StopNative(int handle);
		static int GetStatusNative(int handle, SoundStatus *status);
		static int GetVolumeNative(int handle, float *volume);
		static int SetVolumeNative(int handle, float volume);
		static int GetPanNative(int handle, float *pan);
		static int SetPanNative(int handle, float pan);
		static int GetLoopNative(int, bool *pan);
		static int SetLoopNative(int, bool pan);
		static int GetPlaybackRateNative(int handle, float *rate);
		static int SetPlaybackRateNative(int handle, float rate);
		static int GetPosition(int handle, unsigned long *millisecond);
		static int SetPosition(int handle, unsigned long millisecond);
		static int GetLength(int handle, unsigned long *millisecond);
	};
}
#endif
