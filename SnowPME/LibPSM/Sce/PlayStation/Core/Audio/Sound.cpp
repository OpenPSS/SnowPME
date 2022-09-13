#include "Sound.hpp"

namespace Sce::PlayStation::Core::Audio {
	int Sound::NewFromFilename(string filename, int *handle){
		cout << "Sce::PlayStation::Core::Audio::NewFromFilename(string, int *) Unimplemented." << endl;
		return 0;
	}
	int Sound::NewFromFileImage(byte* fileImage, int *handle){
		cout << "Sce::PlayStation::Core::Audio::NewFromFileImage(byte*, int *) Unimplemented." << endl;
		return 0;
	}
	int Sound::ReleaseNative(int handle){
		cout << "Sce::PlayStation::Core::Audio::ReleaseNative(int) Unimplemented." << endl;
		return 0;
	}
	int Sound::CreatePlayerNative(int handle, int *playerHandle){
		cout << "Sce::PlayStation::Core::Audio::CreatePlayerNative(int, int *) Unimplemented." << endl;
		return 0;
	}
}
