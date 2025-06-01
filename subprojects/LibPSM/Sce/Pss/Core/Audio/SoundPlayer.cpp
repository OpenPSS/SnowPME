#include <Sce/Pss/Core/Audio/SoundPlayer.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Audio {
	int SoundPlayer::ReleaseNative(int handle){
		UNIMPLEMENTED();
	}
	int SoundPlayer::PlayNative(int handle){
		UNIMPLEMENTED();
	}
	int SoundPlayer::StopNative(int handle){
		UNIMPLEMENTED();
	}
	int SoundPlayer::GetStatusNative(int handle, SoundStatus *status){
		UNIMPLEMENTED();
	}
	int SoundPlayer::GetVolumeNative(int handle, float *volume){
		UNIMPLEMENTED();
	}
	int SoundPlayer::SetVolumeNative(int handle, float volume){
		UNIMPLEMENTED();
	}
	int SoundPlayer::GetPanNative(int handle, float *pan){
		UNIMPLEMENTED();
	}
	int SoundPlayer::SetPanNative(int handle, float pan){
		UNIMPLEMENTED();
	}
	int SoundPlayer::GetLoopNative(int handle, bool *pan){
		UNIMPLEMENTED();
	}
	int SoundPlayer::SetLoopNative(int handle, bool pan){
		UNIMPLEMENTED();
	}
	int SoundPlayer::GetPlaybackRateNative(int handle, float *rate){
		UNIMPLEMENTED();
	}
	int SoundPlayer::SetPlaybackRateNative(int handle, float rate){
		UNIMPLEMENTED();
	}
	int SoundPlayer::GetPosition(int handle, unsigned long * millisecond){
		UNIMPLEMENTED();
	}
	int SoundPlayer::SetPosition(int handle, unsigned long millisecond){
		UNIMPLEMENTED();
	}
	int SoundPlayer::GetLength(int handle, unsigned long *millisecond){
		UNIMPLEMENTED();
	}
}
