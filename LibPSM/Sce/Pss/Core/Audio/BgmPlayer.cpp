#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <Sce/Pss/Core/Callback/AudioCallbacks.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <LibShared.hpp>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Callback;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Audio {

	BgmPlayer::BgmPlayer(Bgm* bgm) {
		this->audioBgm = bgm;
	}
	BgmPlayer::~BgmPlayer() {
	}

	int BgmPlayer::ReleaseNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int BgmPlayer::PlayNative(int handle) {
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = (BgmPlayer*)Handles::GetHandle(handle);
			AudioCallbacks::PlayMP3(player->audioBgm->NativeBgmObject);

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
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
