#ifndef LIB_PSS_AUDIOCALLBACKS_H
#define LIB_PSS_AUDIOCALLBACKS_H 1
#include <Sce/Pss/Core/Callback/Callbacks.hpp>
#include <string>

namespace Sce::Pss::Core::Callback {
    class AudioCallbacks : public Callbacks {
	private:
		static void* (*openMp3)(uint8_t* data, size_t dataSz);
		static void  (*closeMp3)(void* bgmObject);
		static bool  (*playMp3)(void* bgmObject, bool loop);
		static void  (*pauseMp3)(void* bgmObject);
		static void  (*resumeMp3)(void* bgmObject);
		static void  (*stopMp3)(void* bgmObject);
		
		static bool  (*isMp3Paused)(void* bgmObject);
		static bool  (*isMp3Playing)(void* bgmObject);
		static bool  (*isMp3Stopped)(void* bgmObject);

		static void  (*setLoop)(void* bgmObject, bool loop);
	public:
		static void Init(void* (*openMp3)(uint8_t*, size_t),
						 void  (*closeMp3)(void* bgmObject),
						 bool  (*playMp3)(void* bgmObject, bool loop),
						 void  (*pauseMp3)(void* bgmObject),
						 void  (*resumeMp3)(void* bgmObject),
			             void  (*stopMp3)(void* bgmObject),
			             bool  (*isMp3Paused)(void* bgmObject),
						 bool  (*isMp3Playing)(void* bgmObject),
						 bool  (*isMp3Stopped)(void* bgmObject),
                		 void  (*setLoop)(void* bgmObject, bool loop));
		static void* OpenMP3(uint8_t* data, size_t dataSz);
		static void CloseMP3(void* bgmObject);
		static bool PlayMP3(void* bgmObject, bool loop);
		static void PauseMP3(void* bgmObject);
		static void ResumeMP3(void* bgmObject);
		static void StopMP3(void* bgmObject);

		static bool IsMP3Paused(void* bgmObject);
		static bool IsMP3Playing(void* bgmObject);
		static bool IsMP3Stopped(void* bgmObject);

		static void SetLoop(void* bgmObject, bool loop);
	};

}

#endif