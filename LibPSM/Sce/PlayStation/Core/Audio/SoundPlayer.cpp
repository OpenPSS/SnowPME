#include "SoundPlayer.hpp"

namespace Sce::PlayStation::Core::Audio {
	int SoundPlayer::ReleaseNative(int handle){
		std::cout << "Sce::PlayStation::Core::Audio::ReleaseNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::PlayNative(int handle){
		std::cout << "Sce::PlayStation::Core::Audio::PlayNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::StopNative(int handle){
		std::cout << "Sce::PlayStation::Core::Audio::StopNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::GetStatusNative(int handle, SoundStatus *status){
		std::cout << "Sce::PlayStation::Core::Audio::GetStatusNative(int, Sce::PlayStation::Core::Audio::SoundStatus *) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::GetVolumeNative(int handle, float *volume){
		std::cout << "Sce::PlayStation::Core::Audio::GetVolumeNative(int, float *) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::SetVolumeNative(int handle, float volume){
		std::cout << "Sce::PlayStation::Core::Audio::SetVolumeNative(int, float) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::GetPanNative(int handle, float *pan){
		std::cout << "Sce::PlayStation::Core::Audio::GetPanNative(int, float *) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::SetPanNative(int handle, float pan){
		std::cout << "Sce::PlayStation::Core::Audio::SetPanNative(int, float) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::GetLoopNative(int handle, bool *pan){
		std::cout << "Sce::PlayStation::Core::Audio::GetLoopNative(int, bool *) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::SetLoopNative(int handle, bool pan){
		std::cout << "Sce::PlayStation::Core::Audio::SetLoopNative(int, bool) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::GetPlaybackRateNative(int handle, float *rate){
		std::cout << "Sce::PlayStation::Core::Audio::GetPlaybackRateNative(int, float *) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::SetPlaybackRateNative(int handle, float rate){
		std::cout << "Sce::PlayStation::Core::Audio::SetPlaybackRateNative(int, float) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::GetPosition(int handle, unsigned long * millisecond){
		std::cout << "Sce::PlayStation::Core::Audio::GetPosition(int, unsigned long *) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::SetPosition(int handle, unsigned long millisecond){
		std::cout << "Sce::PlayStation::Core::Audio::SetPosition(int, unsigned long) Unimplemented." << std::endl;
		return 0;
	}
	int SoundPlayer::GetLength(int handle, unsigned long *millisecond){
		std::cout << "Sce::PlayStation::Core::Audio::GetLength(int, unsigned long *) Unimplemented." << std::endl;
		return 0;
	}
}
