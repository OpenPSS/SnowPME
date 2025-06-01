#include <Sce/Pss/Core/Audio/SoundPlayer.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Audio {
	int SoundPlayer::ReleaseNative(int handle){
		Unimplemented();
	}
	int SoundPlayer::PlayNative(int handle){
		Unimplemented();
	}
	int SoundPlayer::StopNative(int handle){
		Unimplemented();
	}
	int SoundPlayer::GetStatusNative(int handle, SoundStatus *status){
		Unimplemented();
	}
	int SoundPlayer::GetVolumeNative(int handle, float *volume){
		Unimplemented();
	}
	int SoundPlayer::SetVolumeNative(int handle, float volume){
		Unimplemented();
	}
	int SoundPlayer::GetPanNative(int handle, float *pan){
		Unimplemented();
	}
	int SoundPlayer::SetPanNative(int handle, float pan){
		Unimplemented();
	}
	int SoundPlayer::GetLoopNative(int handle, bool *pan){
		Unimplemented();
	}
	int SoundPlayer::SetLoopNative(int handle, bool pan){
		Unimplemented();
	}
	int SoundPlayer::GetPlaybackRateNative(int handle, float *rate){
		Unimplemented();
	}
	int SoundPlayer::SetPlaybackRateNative(int handle, float rate){
		Unimplemented();
	}
	int SoundPlayer::GetPosition(int handle, unsigned long * millisecond){
		Unimplemented();
	}
	int SoundPlayer::SetPosition(int handle, unsigned long millisecond){
		Unimplemented();
	}
	int SoundPlayer::GetLength(int handle, unsigned long *millisecond){
		Unimplemented();
	}
}
