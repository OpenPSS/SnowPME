#include "Sound.hpp"

namespace Sce::PlayStation::Core::Audio {
	int Sound::NewFromFilename(std::string filename, int *handle){
		std::cout << "Sce::PlayStation::Core::Audio::NewFromFilename(string, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Sound::NewFromFileImage(std::byte* fileImage, int *handle){
		std::cout << "Sce::PlayStation::Core::Audio::NewFromFileImage(byte*, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Sound::ReleaseNative(int handle){
		std::cout << "Sce::PlayStation::Core::Audio::ReleaseNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int Sound::CreatePlayerNative(int handle, int *playerHandle){
		std::cout << "Sce::PlayStation::Core::Audio::CreatePlayerNative(int, int *) Unimplemented." << std::endl;
		return 0;
	}
}
