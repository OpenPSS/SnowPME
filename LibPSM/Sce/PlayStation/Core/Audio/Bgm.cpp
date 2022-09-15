#include "Bgm.hpp"

namespace Sce::PlayStation::Core::Audio {
	int Bgm::NewFromFilename(std::string filename, int * handle){
		std::cout << "Sce::PlayStation::Core::Audio::NewFromFilename(string, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Bgm::NewFromFileImage(std::byte* fileImage, int * handle){
		std::cout << "Sce::PlayStation::Core::Audio::NewFromFileImage(byte*, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Bgm::ReleaseNative(int handle){
		std::cout << "Sce::PlayStation::Core::Audio::ReleaseNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int Bgm::CreatePlayerNative(int handle, int * playerHandle){
		std::cout << "Sce::PlayStation::Core::Audio::CreatePlayerNative(int, int *) Unimplemented." << std::endl;
		return 0;
	}
}
