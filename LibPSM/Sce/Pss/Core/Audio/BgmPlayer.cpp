#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <LibShared.hpp>

using namespace Sce::Pss::Core::System;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Audio {

	BgmPlayer::BgmPlayer(Bgm* bgm) {
		this->audioBgm = bgm;
	}
	BgmPlayer::~BgmPlayer() {
		this->audioBgm = nullptr;
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
			return player->audioBgm->AudioImplObject->Play();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::StopNative(int handle){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			return player->audioBgm->AudioImplObject->Stop();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::PauseNative(int handle) {
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			return player->audioBgm->AudioImplObject->Pause();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

	}
	int BgmPlayer::ResumeNative(int handle) {
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			return player->audioBgm->AudioImplObject->Resume();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

	}

	int BgmPlayer::GetStatusNative(int handle, BgmStatus *status){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			if(player->audioBgm->AudioImplObject->Paused())
				*status = BgmStatus::Paused;
			else if (player->audioBgm->AudioImplObject->Playing())
				*status = BgmStatus::Playing;
			else if (player->audioBgm->AudioImplObject->Stopped())
				*status = BgmStatus::Stopped;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::SetVolumeNative(int handle, float volume){
		Logger::Debug(__FUNCTION__);

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			return player->audioBgm->AudioImplObject->SetVolume(volume);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetVolumeNative(int handle, float *volume){
		Logger::Debug(__FUNCTION__);
		if (volume == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			*volume = player->audioBgm->AudioImplObject->Volume();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLoopNative(int handle, bool *pan){
		Logger::Debug(__FUNCTION__);
		if (pan == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			
			*pan = player->audioBgm->AudioImplObject->Looping();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetLoopNative(int handle, bool pan){
		Logger::Debug(__FUNCTION__);
		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);
			player->audioBgm->AudioImplObject->SetLooping(pan);

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
		Logger::Debug(__FUNCTION__);
		if (milisecond == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			*milisecond = player->audioBgm->AudioImplObject->Time();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetPosition(int handle, unsigned long milisecond){
		Logger::Debug(__FUNCTION__);

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			return player->audioBgm->AudioImplObject->SetTime(milisecond);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLength(int handle, unsigned long *milisecond){
		Logger::Debug(__FUNCTION__);
		if (milisecond == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			*milisecond = player->audioBgm->AudioImplObject->Duration();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLoopPosition(int handle, unsigned long *msStart, unsigned long *msEnd){
		Logger::Debug(__FUNCTION__);
		if (msEnd == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (msStart == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			*msStart = player->audioBgm->AudioImplObject->LoopStart();
			*msEnd = player->audioBgm->AudioImplObject->LoopEnd();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetLoopPosition(int handle, unsigned long msStart, unsigned long msEnd){
		Logger::Debug(__FUNCTION__);

		if (Handles::IsValid(handle)) {
			BgmPlayer* player = Handles::Get<BgmPlayer>(handle);

			// check msStart & msEnd are not outside the range
			if (msStart > player->audioBgm->AudioImplObject->Duration()) return PSM_ERROR_OUT_OF_RANGE;
			if (msEnd > player->audioBgm->AudioImplObject->Duration()) return PSM_ERROR_OUT_OF_RANGE;

			if (player->audioBgm->AudioImplObject->SetLoopStart(msStart) != PSM_ERROR_NO_ERROR) return PSM_ERROR_COMMON_INVALID_OPERATION;
			if (player->audioBgm->AudioImplObject->SetLoopEnd(msStart) != PSM_ERROR_NO_ERROR) return PSM_ERROR_COMMON_INVALID_OPERATION;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
}
