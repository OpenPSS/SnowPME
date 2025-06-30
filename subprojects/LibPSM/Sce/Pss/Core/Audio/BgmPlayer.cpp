#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <LibShared.hpp>

using namespace Sce::Pss::Core::System;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Audio {

	BgmPlayer::BgmPlayer(std::weak_ptr<Bgm> bgm) {
		this->audioBgm = bgm;
	}

	int BgmPlayer::ReleaseNative(int handle){
		LOG_FUNCTION();
		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			BgmPlayer::Delete(player);
		}
		return PSM_ERROR_NO_ERROR;
	}
	int BgmPlayer::PlayNative(int handle) {
		LOG_FUNCTION();
		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			return player->audioBgm.lock()->AudioImplObject->Play();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::StopNative(int handle){
		LOG_FUNCTION();
		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			return player->audioBgm.lock()->AudioImplObject->Stop();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::PauseNative(int handle) {
		LOG_FUNCTION();
		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			return player->audioBgm.lock()->AudioImplObject->Pause();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

	}
	int BgmPlayer::ResumeNative(int handle) {
		LOG_FUNCTION();
		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			return player->audioBgm.lock()->AudioImplObject->Resume();
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;

	}

	int BgmPlayer::GetStatusNative(int handle, BgmStatus *status){
		LOG_FUNCTION();
		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			if(player->audioBgm.lock()->AudioImplObject->Paused())
				*status = BgmStatus::Paused;
			else if (player->audioBgm.lock()->AudioImplObject->Playing())
				*status = BgmStatus::Playing;
			else if (player->audioBgm.lock()->AudioImplObject->Stopped())
				*status = BgmStatus::Stopped;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::SetVolumeNative(int handle, float volume){
		LOG_FUNCTION();

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			return player->audioBgm.lock()->AudioImplObject->SetVolume(volume);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetVolumeNative(int handle, float *volume){
		LOG_FUNCTION();
		if (volume == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			*volume = player->audioBgm.lock()->AudioImplObject->Volume();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLoopNative(int handle, bool *pan){
		LOG_FUNCTION();
		if (pan == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			
			*pan = player->audioBgm.lock()->AudioImplObject->Looping();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetLoopNative(int handle, bool pan){
		LOG_FUNCTION();
		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			player->audioBgm.lock()->AudioImplObject->SetLooping(pan);

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::GetPlaybackRateNative(int handle, float *rate){
		LOG_FUNCTION();
		
		if (rate == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);
			
			*rate = player->audioBgm.lock()->AudioImplObject->PlaybackSpeed();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetPlaybackRateNative(int handle, float rate){
		LOG_FUNCTION();

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			return player->audioBgm.lock()->AudioImplObject->SetPlaybackSpeed(rate);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::GetPosition(int handle, unsigned long *milisecond){
		LOG_FUNCTION();
		if (milisecond == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			*milisecond = player->audioBgm.lock()->AudioImplObject->Time();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::SetPosition(int handle, unsigned long milisecond){
		LOG_FUNCTION();

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			return player->audioBgm.lock()->AudioImplObject->SetTime(milisecond);
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLength(int handle, unsigned long *milisecond){
		LOG_FUNCTION();
		if (milisecond == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			*milisecond = player->audioBgm.lock()->AudioImplObject->Duration();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int BgmPlayer::GetLoopPosition(int handle, unsigned long *msStart, unsigned long *msEnd){
		LOG_FUNCTION();
		if (msEnd == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (msStart == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			*msStart = player->audioBgm.lock()->AudioImplObject->LoopStart();
			*msEnd = player->audioBgm.lock()->AudioImplObject->LoopEnd();

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}

	int BgmPlayer::SetLoopPosition(int handle, unsigned long msStart, unsigned long msEnd){
		LOG_FUNCTION();

		if (Handles<BgmPlayer>::IsValid(handle)) {
			std::shared_ptr<BgmPlayer> player = Handles<BgmPlayer>::Get(handle);

			// check msStart & msEnd are not outside the range
			if (msStart > player->audioBgm.lock()->AudioImplObject->Duration()) return PSM_ERROR_OUT_OF_RANGE;
			if (msEnd > player->audioBgm.lock()->AudioImplObject->Duration()) return PSM_ERROR_OUT_OF_RANGE;

			if (player->audioBgm.lock()->AudioImplObject->SetLoopStart(msStart) != PSM_ERROR_NO_ERROR) return PSM_ERROR_COMMON_INVALID_OPERATION;
			if (player->audioBgm.lock()->AudioImplObject->SetLoopEnd(msStart) != PSM_ERROR_NO_ERROR) return PSM_ERROR_COMMON_INVALID_OPERATION;

			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
}
