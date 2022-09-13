#ifndef LIB_PSM_BGMPLAYER_H
#define LIB_PSM_BGMPLAYER_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "BgmStatus.hpp"

using namespace std;
namespace Sce::PlayStation::Core::Audio {
	class BgmPlayer {
	public:
		static int ReleaseNative(int handle);
		static int PlayNative(int handle);
		static int StopNative(int handle);
		static int GetStatusNative(int handle, BgmStatus *status);
		static int PauseNative(int handle);
		static int ResumeNative(int handle);
		static int SetVolumeNative(int handle, float volume);
		static int GetVolumeNative(int handle, float *volume);
		static int GetLoopNative(int handle, bool *pan);
		static int SetLoopNative(int handle, bool pan);
		static int GetPlaybackRateNative(int handle, float *rate);
		static int SetPlaybackRateNative(int handle, float rate);
		static int GetPosition(int handle, unsigned long *millisecond);
		static int SetPosition(int handle, unsigned long millisecond);
		static int GetLength(int handle, unsigned long *millisecond);
		static int GetLoopPosition(int handle, unsigned long *msStart, unsigned long *msEnd);
		static int SetLoopPosition(int handle, unsigned long msStart, unsigned long msEnd);
	};
}
#endif
