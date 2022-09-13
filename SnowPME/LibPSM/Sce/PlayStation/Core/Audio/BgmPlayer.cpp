#include "BgmPlayer.hpp"

namespace Sce::PlayStation::Core::Audio {
	int BgmPlayer::ReleaseNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::ReleaseNative(int) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::PlayNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::PlayNative(int) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::StopNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::StopNative(int) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::GetStatusNative(int handle, BgmStatus *status){
		cout << "Sce::PlayStation::Core::Audio::GetStatusNative(int, Sce::PlayStation::Core::Audio::BgmStatus *) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::PauseNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::PauseNative(int) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::ResumeNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::ResumeNative(int) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::SetVolumeNative(int handle, float volume){
		cout << "Sce::PlayStation::Core::Audio::SetVolumeNative(int, float) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::GetVolumeNative(int handle, float *volume){
		cout << "Sce::PlayStation::Core::Audio::GetVolumeNative(int, float *) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::GetLoopNative(int handle, bool *pan){
		cout << "Sce::PlayStation::Core::Audio::GetLoopNative(int, bool *) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::SetLoopNative(int handle, bool pan){
		cout << "Sce::PlayStation::Core::Audio::SetLoopNative(int, bool) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::GetPlaybackRateNative(int handle, float *rate){
		cout << "Sce::PlayStation::Core::Audio::GetPlaybackRateNative(int, float *) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::SetPlaybackRateNative(int handle, float rate){
		cout << "Sce::PlayStation::Core::Audio::SetPlaybackRateNative(int, float) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::GetPosition(int handle, unsigned long *milisecond){
		cout << "Sce::PlayStation::Core::Audio::GetPosition(int, unsigned long *) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::SetPosition(int handle, unsigned long milisecond){
		cout << "Sce::PlayStation::Core::Audio::SetPosition(int, unsigned long) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::GetLength(int handle, unsigned long *milisecond){
		cout << "Sce::PlayStation::Core::Audio::GetLength(int, unsigned long *) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::GetLoopPosition(int handle, unsigned long *msStart, unsigned long *msEnd){
		cout << "Sce::PlayStation::Core::Audio::GetLoopPosition(int, unsigned long *, unsigned long *) Unimplemented." << endl;
		return 0;
	}
	int BgmPlayer::SetLoopPosition(int handle, unsigned long msStart, unsigned long msEnd){
		cout << "Sce::PlayStation::Core::Audio::SetLoopPosition(int, unsigned long, unsigned long) Unimplemented." << endl;
		return 0;
	}
}
