#include "SoundPlayer.hpp"

namespace Sce::PlayStation::Core::Audio {
	int SoundPlayer::ReleaseNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::ReleaseNative(int) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::PlayNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::PlayNative(int) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::StopNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::StopNative(int) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::GetStatusNative(int handle, SoundStatus *status){
		cout << "Sce::PlayStation::Core::Audio::GetStatusNative(int, Sce::PlayStation::Core::Audio::SoundStatus *) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::GetVolumeNative(int handle, float *volume){
		cout << "Sce::PlayStation::Core::Audio::GetVolumeNative(int, float *) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::SetVolumeNative(int handle, float volume){
		cout << "Sce::PlayStation::Core::Audio::SetVolumeNative(int, float) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::GetPanNative(int handle, float *pan){
		cout << "Sce::PlayStation::Core::Audio::GetPanNative(int, float *) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::SetPanNative(int handle, float pan){
		cout << "Sce::PlayStation::Core::Audio::SetPanNative(int, float) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::GetLoopNative(int handle, bool *pan){
		cout << "Sce::PlayStation::Core::Audio::GetLoopNative(int, bool *) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::SetLoopNative(int handle, bool pan){
		cout << "Sce::PlayStation::Core::Audio::SetLoopNative(int, bool) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::GetPlaybackRateNative(int handle, float *rate){
		cout << "Sce::PlayStation::Core::Audio::GetPlaybackRateNative(int, float *) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::SetPlaybackRateNative(int handle, float rate){
		cout << "Sce::PlayStation::Core::Audio::SetPlaybackRateNative(int, float) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::GetPosition(int handle, unsigned long * millisecond){
		cout << "Sce::PlayStation::Core::Audio::GetPosition(int, unsigned long *) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::SetPosition(int handle, unsigned long millisecond){
		cout << "Sce::PlayStation::Core::Audio::SetPosition(int, unsigned long) Unimplemented." << endl;
		return 0;
	}
	int SoundPlayer::GetLength(int handle, unsigned long *millisecond){
		cout << "Sce::PlayStation::Core::Audio::GetLength(int, unsigned long *) Unimplemented." << endl;
		return 0;
	}
}
