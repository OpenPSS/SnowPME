#ifndef LIB_PSS_AUDIOCALLBACKS_H
#define LIB_PSS_AUDIOCALLBACKS_H 1
#include <string>

namespace Sce::Pss::Core::Callback {
	class AudioCallbacks {
	private:
		static bool isInitalized;
		static void* (*openMp3)(uint8_t* data, size_t dataSz);
		static void  (*closeMp3)(void* bgmObject);
	public:
		static void Init(void* (*openMp3)(uint8_t*, size_t),
						 void  (*closeMp3)(void* bgmObject));
		static void* OpenMP3(uint8_t* data, size_t dataSz);
		static void CloseMP3(void* bgmObject);
	};

}

#endif