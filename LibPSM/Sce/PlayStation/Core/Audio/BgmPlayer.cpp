#include "BgmPlayer.hpp"

namespace Sce::PlayStation::Core::Audio {
	int BgmPlayer::ReleaseNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::PlayNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::StopNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::GetStatusNative(int handle, BgmStatus *status){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::PauseNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::ResumeNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::SetVolumeNative(int handle, float volume){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::GetVolumeNative(int handle, float *volume){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::GetLoopNative(int handle, bool *pan){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::SetLoopNative(int handle, bool pan){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::GetPlaybackRateNative(int handle, float *rate){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::SetPlaybackRateNative(int handle, float rate){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::GetPosition(int handle, unsigned long *milisecond){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::SetPosition(int handle, unsigned long milisecond){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::GetLength(int handle, unsigned long *milisecond){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::GetLoopPosition(int handle, unsigned long *msStart, unsigned long *msEnd){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::SetLoopPosition(int handle, unsigned long msStart, unsigned long msEnd){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
