#include "Bgm.hpp"

namespace Sce::PlayStation::Core::Audio {
	int Bgm::NewFromFilename(std::string filename, int * handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Bgm::NewFromFileImage(std::byte* fileImage, int * handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Bgm::ReleaseNative(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Bgm::CreatePlayerNative(int handle, int * playerHandle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
