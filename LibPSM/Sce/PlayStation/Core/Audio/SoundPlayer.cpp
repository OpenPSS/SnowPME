#include "SoundPlayer.hpp"

namespace Sce::PlayStation::Core::Audio {
	int SoundPlayer::ReleaseNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::PlayNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::StopNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::GetStatusNative(int handle, SoundStatus *status){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::GetVolumeNative(int handle, float *volume){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::SetVolumeNative(int handle, float volume){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::GetPanNative(int handle, float *pan){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::SetPanNative(int handle, float pan){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::GetLoopNative(int handle, bool *pan){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::SetLoopNative(int handle, bool pan){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::GetPlaybackRateNative(int handle, float *rate){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::SetPlaybackRateNative(int handle, float rate){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::GetPosition(int handle, unsigned long * millisecond){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::SetPosition(int handle, unsigned long millisecond){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SoundPlayer::GetLength(int handle, unsigned long *millisecond){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
