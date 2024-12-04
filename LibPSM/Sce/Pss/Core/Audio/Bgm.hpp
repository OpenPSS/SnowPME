#ifndef LIB_PSS_BGM_H
#define LIB_PSS_BGM_H 1
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Audio/Impl/Audio.hpp>
#include <string>
#include <iostream>
#include <mono/mono.h>
#include <atomic>
namespace Sce::Pss::Core::Audio {
	class Bgm : public PsmObject<Bgm> {
		uint8_t* audioData = nullptr;
		uint32_t audioSz = 0;

		bool isMp3();
	public:
		Impl::Audio* AudioImplObject = nullptr;
		Bgm(const std::string& filename);
		Bgm(uint8_t* data, int dataSz);
		~Bgm();
		static int NewFromFilename(MonoString* filename, int* handle);
		static int NewFromFileImage(MonoArray* fileImage, int* handle);
		static int ReleaseNative(int handle);
		static int CreatePlayerNative(int handle, int* playerHandle);
	};
}
#endif
