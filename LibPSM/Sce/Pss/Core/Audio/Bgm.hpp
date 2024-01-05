#ifndef LIB_PSS_BGM_H
#define LIB_PSS_BGM_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <string>
#include <iostream>
#include <mono/mono.h>

namespace Sce::Pss::Core::Audio {
	class Bgm : public PsmObject{
		uint8_t* audioData = nullptr;
		uint32_t audioSz = 0;

		void* bgmObject = nullptr;

		bool isMp3();
	public:
		Bgm(std::string filename);
		static int NewFromFilename(MonoString* filename, int* handle);
		static int NewFromFileImage(uint8_t* fileImage, int* handle);
		static int ReleaseNative(int handle);
		static int CreatePlayerNative(int handle, int* playerHandle);
	};
}
#endif
