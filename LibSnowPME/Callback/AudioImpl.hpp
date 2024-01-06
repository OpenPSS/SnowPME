#ifndef SNOW_PME_AUDIOIMPL_H
#define SNOW_PME_AUDIOIMPL_H 1
#include <iostream>
#include <Callback/Impl.hpp>
namespace SnowPME::Callback {

	class AudioImpl : public Impl{
	public:
		static void Init();
		static void* OpenMP3(uint8_t* data, size_t dataSz);
		static void CloseMP3(void* bgmObject);
		static void PlayMP3(void* bgmObject);
	};

}

#endif