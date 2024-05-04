#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <Sce/Pss/Core/Callback/AudioCallbacks.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <LibShared.hpp>

namespace Sce::Pss::Core::Audio {
	using namespace Sce::Pss::Core::System;
	using namespace Sce::Pss::Core::Callback;
	using namespace Shared::Debug;

	BgmPlayer::BgmPlayer(Bgm* bgm) {
		this->audioBgm = bgm;
	}
	BgmPlayer::~BgmPlayer() {
	}

	int BgmPlayer::ReleaseNative(int handle){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			delete player;
		}
		return PSM_ERROR_NO_ERROR;
	}
	int BgmPlayer::PlayNative(int handle) {
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			if (!AudioCallbacks::PlayMP3(player->audioBgm->NativeBgmObject, player->loop)) {
				return PSM_ERROR_AUDIO_SYSTEM;
			}

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::StopNative(int handle){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			AudioCallbacks::StopMP3(player->audioBgm->NativeBgmObject);

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetStatusNative(int handle, BgmStatus *status){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			if(AudioCallbacks::IsMP3Paused(player->audioBgm->NativeBgmObject))
				*status = BgmStatus::Paused;
			else if (AudioCallbacks::IsMP3Playing(player->audioBgm->NativeBgmObject))
				*status = BgmStatus::Playing;
			else if (AudioCallbacks::IsMP3Stopped(player->audioBgm->NativeBgmObject))
				*status = BgmStatus::Stopped;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::PauseNative(int handle){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			AudioCallbacks::PauseMP3(player->audioBgm->NativeBgmObject);

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

	}
	int BgmPlayer::ResumeNative(int handle){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			AudioCallbacks::ResumeMP3(player->audioBgm->NativeBgmObject);

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

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
		Logger::Debug(__FUNCTION__);
		if (pan == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			
			*pan = player->loop;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetLoopNative(int handle, bool pan){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			player->loop = pan;
			AudioCallbacks::SetLoop(player->audioBgm->NativeBgmObject, player->loop);

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
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
