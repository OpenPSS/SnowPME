#include <Sce/Pss/Core/Audio/Bgm.hpp>
#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Callback/AudioCallbacks.hpp>
#include <LibShared.hpp>
#include <mono/mono.h>
#include <iostream>
#include <string.h>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Callback;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Audio {
	bool Bgm::isMp3() {
		if (this->audioSz >= 3) {
			if (memcmp(this->audioData, "ID3", 3) == 0) {
				return true;
			}
		}
		return false;
	}

	Bgm::~Bgm() {
		HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();
		if(this->audioData != nullptr)
			allocator->sce_psm_free(this->audioData);

		if (this->NativeBgmObject != nullptr)
			AudioCallbacks::CloseMP3(this->NativeBgmObject);

	}
	Bgm::Bgm(uint8_t* data, int dataSz) {
		// set audioData and size 
		this->audioData = data;
		this->audioSz = dataSz;

		if (this->isMp3()) { // check data is an MP3 file
			this->NativeBgmObject = AudioCallbacks::OpenMP3(this->audioData, this->audioSz); // send it to the audio engine !
		}
		else {
			this->SetError(PSM_ERROR_COMMON_INVALID_FORMAT);
		}
	}

	Bgm::Bgm(std::string filename) {
		uint64_t file = NULL;
		// Open the file specified
		if (ICall::PsmFileOpen((char*)filename.c_str(), SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ, &file) == PSM_ERROR_NO_ERROR) {
			// get total file sie..
			ICall::PsmFileGetSize(file, &this->audioSz);
			
			// allocate enough space in memory for this audio file
			HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();
			this->audioData = allocator->sce_psm_malloc(this->audioSz);

			if (this->audioData != nullptr) {
				// read the audio file into memory
				uint32_t bytesRead = 0;
				ICall::PsmFileRead(file, this->audioData, this->audioSz, &bytesRead);
				ICall::PsmClose(file);

				if (this->audioSz == bytesRead) {
					if (!this->isMp3()) { // ensure file is an mp3
						this->NativeBgmObject = AudioCallbacks::OpenMP3(this->audioData, this->audioSz); // send it to the audio engine !
					}
					else {
						this->SetError(PSM_ERROR_COMMON_INVALID_FORMAT);
					}
				}
				else {
					this->SetError(PSM_ERROR_COMMON_IO);
				}
			}
			else {
				ICall::PsmClose(file);
				this->SetError(PSM_ERROR_OUT_OF_MEMORY);
			}
		}
		else {
			this->SetError(PSM_ERROR_COMMON_FILE_NOT_FOUND);
		}

	}

	int Bgm::NewFromFilename(MonoString* filename, int * handle){
		Logger::Debug(__FUNCTION__);

		if (filename == nullptr || handle == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		char* fname = mono_string_to_utf8(filename);
		
		if (fname == nullptr)
			return PSM_ERROR_COMMON_OUT_OF_MEMORY;


		std::string audioFileName = std::string(fname);
		mono_free(fname);

		Bgm* bgm = new Bgm(audioFileName);
		ReturnErrorable(bgm);
		*handle = bgm->Handle;

		return PSM_ERROR_NO_ERROR;
	}

	int Bgm::NewFromFileImage(MonoArray* fileImage, int* handle) {
		Logger::Debug(__FUNCTION__);

		if (fileImage == nullptr || handle == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		char* fImage = mono_array_addr_with_size(fileImage, 1, 0);
		int fSz = mono_array_length(fileImage);

		HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();
		uint8_t* musicData = allocator->sce_psm_malloc(fSz);
		if (musicData != nullptr) {
			memcpy(musicData, fImage, fSz);
			Bgm* bgm = new Bgm(musicData, fSz);
			ReturnErrorable(bgm);
			*handle = bgm->Handle;

			return PSM_ERROR_NO_ERROR;
		}
		else {
			return PSM_ERROR_OUT_OF_MEMORY;
		}
	}

	int Bgm::ReleaseNative(int handle) {
		Logger::Debug(__FUNCTION__);
		
		if (Handles::IsValid(handle)) {
			Bgm* bgm = (Bgm*)Handles::GetHandle(handle);
			delete bgm;
		}

		return PSM_ERROR_NO_ERROR;
	}
	int Bgm::CreatePlayerNative(int handle, int* playerHandle) {
		Logger::Debug(__FUNCTION__);
		if (playerHandle == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			Bgm* bgm = (Bgm*)Handles::GetHandle(handle);
			BgmPlayer* player = new BgmPlayer(bgm);

			if (Handles::IsValid(player->Handle)) {
				*playerHandle = player->Handle;
			}
			else {
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}
		}
		else {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		return PSM_ERROR_NO_ERROR;
	}
}
