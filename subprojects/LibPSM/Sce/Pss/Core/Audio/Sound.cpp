#include <Sce/Pss/Core/Audio/Sound.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Audio {
	int Sound::NewFromFilename(MonoString* filename, int *handle){
		Unimplemented();
	}
	int Sound::NewFromFileImage(MonoArray* fileImage, int *handle){
		Unimplemented();
	}
	int Sound::ReleaseNative(int handle){
		Unimplemented();
	}
	int Sound::CreatePlayerNative(int handle, int *playerHandle){
		Unimplemented();
	}
}
