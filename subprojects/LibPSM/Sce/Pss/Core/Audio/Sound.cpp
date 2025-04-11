#include <Sce/Pss/Core/Audio/Sound.hpp>

namespace Sce::Pss::Core::Audio {
	int Sound::NewFromFilename(MonoString* filename, int *handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Sound::NewFromFileImage(MonoArray* fileImage, int *handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Sound::ReleaseNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Sound::CreatePlayerNative(int handle, int *playerHandle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
