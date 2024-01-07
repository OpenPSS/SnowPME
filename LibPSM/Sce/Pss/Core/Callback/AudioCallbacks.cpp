#include <Sce/Pss/Core/Callback/AudioCallbacks.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Callback {


	void*   (*AudioCallbacks::openMp3)(uint8_t* data, size_t dataSz) = nullptr;
	void	(*AudioCallbacks::closeMp3)(void* bgmObject) = nullptr;
	bool	(*AudioCallbacks::playMp3)(void* bgmObject, bool loop) = nullptr;
	void	(*AudioCallbacks::pauseMp3)(void* bgmObject) = nullptr;
	void	(*AudioCallbacks::resumeMp3)(void* bgmObject) = nullptr;
	void	(*AudioCallbacks::setLoop)(void* bgmObject, bool loop) = nullptr;


	void AudioCallbacks::Init(void* (*openMp3)(uint8_t*, size_t),
							  void  (*closeMp3)(void* bgmObject),
						      bool  (*playMp3)(void* bgmObject, bool loop),
							  void  (*pauseMp3)(void* bgmObject),
							  void  (*resumeMp3)(void* bgmObject),
							  void  (*setLoop)(void* bgmObject, bool loop)) {
		AudioCallbacks::openMp3 = openMp3;
		AudioCallbacks::closeMp3 = closeMp3;
		AudioCallbacks::playMp3 = playMp3;
		AudioCallbacks::pauseMp3 = pauseMp3;
		AudioCallbacks::resumeMp3 = resumeMp3;
		AudioCallbacks::setLoop = setLoop;

		AudioCallbacks::isInitalized = true;
	}
	
	void AudioCallbacks::CloseMP3(void* bgmObject) {
		errorOnNotInitalized();
		closeMp3(bgmObject);
	}

	bool AudioCallbacks::PlayMP3(void* bgmObject, bool loop) {
		errorOnNotInitalized();
		return playMp3(bgmObject, loop);
	}

	void* AudioCallbacks::OpenMP3(uint8_t* data, size_t dataSz) {
		errorOnNotInitalized();
		return openMp3(data, dataSz);
	}
	void AudioCallbacks::ResumeMP3(void* bgmObject) {
		errorOnNotInitalized();
		resumeMp3(bgmObject);
	}

	void AudioCallbacks::PauseMP3(void* bgmObject) {
		errorOnNotInitalized();
		pauseMp3(bgmObject);
	}

	void AudioCallbacks::SetLoop(void* bgmObject, bool loop) {
		errorOnNotInitalized();
		setLoop(bgmObject, loop);
	}
}