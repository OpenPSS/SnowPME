#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <LibShared.hpp>

using namespace Sce::Pss::Core::System;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Audio {

	BgmPlayer::BgmPlayer(int bgmHandle) {
		this->bgmHandle = bgmHandle;
	}

	int BgmPlayer::ReleaseNative(int handle){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer::Delete(handle);
		}
		return PSM_ERROR_NO_ERROR;
	}
	int BgmPlayer::PlayNative(int handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			return Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Play();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::StopNative(int handle){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			return Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Stop();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::PauseNative(int handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			return Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Pause();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

	}
	int BgmPlayer::ResumeNative(int handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			return Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Resume();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

	}

	int BgmPlayer::GetStatusNative(int handle, BgmStatus *status){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			if(Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Paused())
				*status = BgmStatus::Paused;
			else if (Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Playing())
				*status = BgmStatus::Playing;
			else if (Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Stopped())
				*status = BgmStatus::Stopped;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::SetVolumeNative(int handle, float volume){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			return Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->SetVolume(volume);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetVolumeNative(int handle, float *volume){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (volume == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			*volume = Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Volume();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLoopNative(int handle, bool *pan){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (pan == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			
			*pan = Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Looping();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetLoopNative(int handle, bool pan){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->SetLooping(pan);

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::GetPlaybackRateNative(int handle, float *rate){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (rate == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);
			
			*rate = Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->PlaybackSpeed();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetPlaybackRateNative(int handle, float rate){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			return Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->SetPlaybackSpeed(rate);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::GetPosition(int handle, unsigned long *milisecond){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (milisecond == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			*milisecond = Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Time();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetPosition(int handle, unsigned long milisecond){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			return Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->SetTime(milisecond);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLength(int handle, unsigned long *milisecond){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (milisecond == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			*milisecond = Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Duration();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLoopPosition(int handle, unsigned long *msStart, unsigned long *msEnd){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (msEnd == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (msStart == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			*msStart = Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->LoopStart();
			*msEnd = Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->LoopEnd();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::SetLoopPosition(int handle, unsigned long msStart, unsigned long msEnd){
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (BgmPlayer::CheckHandle(handle)) {
			BgmPlayer* player = BgmPlayer::LookupHandle(handle);

			// check msStart & msEnd are not outside the range
			if (msStart > Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Duration()) return PSM_ERROR_OUT_OF_RANGE;
			if (msEnd > Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->Duration()) return PSM_ERROR_OUT_OF_RANGE;

			if (Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->SetLoopStart(msStart) != PSM_ERROR_NO_ERROR) return PSM_ERROR_COMMON_INVALID_OPERATION;
			if (Bgm::LookupHandle(player->bgmHandle)->AudioImplObject->SetLoopEnd(msStart) != PSM_ERROR_NO_ERROR) return PSM_ERROR_COMMON_INVALID_OPERATION;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
}
