#include <Sce/Pss/Core/Audio/Bgm.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Callback/AudioCallbacks.hpp>
#include <mono/mono.h>
#include <iostream>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Callback;

namespace Sce::Pss::Core::Audio {
	bool Bgm::isMp3() {
		if (this->audioSz >= 3) {
			if (memcmp(this->audioData, "ID3", 3) == 0) {
				return true;
			}
		}
		return false;
	}

	Bgm::Bgm(std::string filename) {
		uint64_t file = NULL;
		if (ICall::PsmFileOpen((char*)filename.c_str(), SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ, &file) == PSM_ERROR_NO_ERROR) {
			ICall::PsmFileGetSize(file, &this->audioSz);
			
			HeapAllocator* allocator = HeapAllocator::GetResourceHeapAllocator();
			this->audioData = allocator->sce_psm_malloc(this->audioSz);

			if (this->audioData != nullptr) {
				uint32_t bytesRead = 0;
				ICall::PsmFileRead(file, this->audioData, this->audioSz, &bytesRead);
				ICall::PsmClose(file);

				if (this->audioSz == bytesRead) {
					if (!this->isMp3()) {
						this->bgmObject = AudioCallbacks::OpenMP3(this->audioData, this->audioSz);
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
		if (filename == nullptr || handle == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		char* fname = mono_string_to_utf8(filename);
		
		if (fname == nullptr)
			return PSM_ERROR_COMMON_OUT_OF_MEMORY;


		std::string audioFileName = std::string(fname);
		mono_free(fname);

		Bgm* bgm = new Bgm(audioFileName);
		ReturnErrorable(bgm);
		*handle = Handles::CreateHandle((uintptr_t)bgm);

		return PSM_ERROR_NO_ERROR;
	}
	int Bgm::NewFromFileImage(uint8_t* fileImage, int * handle){
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
