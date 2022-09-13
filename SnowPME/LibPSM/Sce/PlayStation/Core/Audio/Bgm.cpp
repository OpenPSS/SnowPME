#include "Bgm.hpp"

namespace Sce::PlayStation::Core::Audio {
	int Bgm::NewFromFilename(string filename, int * handle){
		cout << "Sce::PlayStation::Core::Audio::NewFromFilename(string, int *) Unimplemented." << endl;
		return 0;
	}
	int Bgm::NewFromFileImage(byte* fileImage, int * handle){
		cout << "Sce::PlayStation::Core::Audio::NewFromFileImage(byte*, int *) Unimplemented." << endl;
		return 0;
	}
	int Bgm::ReleaseNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::ReleaseNative(int) Unimplemented." << endl;
		return 0;
	}
	int Bgm::CreatePlayerNative(int handle, int * playerHandle){
		cout << "Sce::PlayStation::Core::Audio::CreatePlayerNative(int, int *) Unimplemented." << endl;
		return 0;
	}
}
