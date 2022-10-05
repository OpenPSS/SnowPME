#include "Sound.hpp"

namespace Sce::PlayStation::Core::Audio {
	int Sound::NewFromFilename(std::string filename, int *handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Sound::NewFromFileImage(std::byte* fileImage, int *handle){
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
