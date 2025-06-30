#include <Sce/Pss/Core/Audio/Bgm.hpp>
#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Audio/Impl/AudioImpl.hpp>

#include <LibShared.hpp>

#include <mono/mono.h>
#include <iostream>
#include <string.h>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Memory;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Audio {

	bool Bgm::isMp3() {
		if (this->audioData.size() >= 3) {
			uint8_t mp3Magic[0x2]  = { 0xFF, 0xFA };
			uint8_t mp3Magic2[0x2] = { 0xFF, 0xFB };
			uint8_t mp3Magic3[0x2] = { 0xFF, 0xFE };
			uint8_t id3Magic[0x3]  = { 0x49, 0x44, 0x33 };

			if (memcmp(this->audioData.data(), mp3Magic, sizeof(mp3Magic)) == 0 || 
				memcmp(this->audioData.data(), mp3Magic2, sizeof(mp3Magic2)) == 0 ||
				memcmp(this->audioData.data(), mp3Magic3, sizeof(mp3Magic3)) == 0 ||
				memcmp(this->audioData.data(), id3Magic, sizeof(id3Magic)) == 0) {
				return true;
			}
		}
		return false;
	}

	Bgm::~Bgm() {
		this->AudioImplObject = nullptr;
	}
	Bgm::Bgm(uint8_t* data, int dataSz) {
		// set audioData and size
		this->audioData.resize(dataSz);
		memcpy(this->audioData.data(), data, dataSz);

		if (this->isMp3()) { // check data is an MP3 file
			this->AudioImplObject = std::make_unique<Impl::AudioImpl>(this->audioData); // send it to the audio engine !
			this->SetError(this->AudioImplObject->GetError());
		}
		else {
			this->SetError(PSM_ERROR_COMMON_INVALID_FORMAT);
		}
	}

	Bgm::Bgm(const std::string& filename) {
		uint64_t file = 0;
		// Open the file specified
		if (IoCall::PsmFileOpen((char*)filename.c_str(), SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ, &file) == PSM_ERROR_NO_ERROR) {
			uint32_t audioSz = 0;

			// get total file size..
			IoCall::PsmFileGetSize(file, &audioSz);

			this->audioData.resize(audioSz);

			if (this->audioData.size() == audioSz) {
				// read the audio file into memory
				uint32_t bytesRead = 0;
				IoCall::PsmFileRead(file, this->audioData.data(), audioSz, &bytesRead);
				IoCall::PsmClose(file);

				if (audioSz == bytesRead) {
					if (this->isMp3()) { // ensure file is an mp3
						this->AudioImplObject = std::make_unique<Impl::AudioImpl>(this->audioData); // send it to the audio engine !
						this->SetError(this->AudioImplObject->GetError());
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
				IoCall::PsmClose(file);
				this->SetError(PSM_ERROR_OUT_OF_MEMORY);
			}
		}
		else {
			this->SetError(PSM_ERROR_COMMON_FILE_NOT_FOUND);
		}

	}

	int Bgm::NewFromFilename(MonoString* filename, int* handle){
		LOG_FUNCTION();

		if (filename == nullptr || handle == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		char* fname = mono_string_to_utf8(filename);
		
		if (fname == nullptr)
			return PSM_ERROR_COMMON_OUT_OF_MEMORY;


		std::string audioFileName = std::string(fname);
		mono_free(fname);

		Bgm* bgm = new Bgm(audioFileName);
		RETURN_ERRORABLE(bgm);
		*handle = bgm->Handle();

		return PSM_ERROR_NO_ERROR;
	}

	int Bgm::NewFromFileImage(MonoArray* fileImage, int* handle) {
		LOG_FUNCTION();

		if (fileImage == nullptr || handle == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		char* fImage = mono_array_addr_with_size(fileImage, 1, 0);
		int fSz = mono_array_length(fileImage);

		std::shared_ptr<HeapAllocator> allocator = HeapAllocator::UniqueObject();
		uint8_t* musicData = reinterpret_cast<uint8_t*>(allocator->sce_psm_malloc(fSz));

		if (musicData != nullptr) {
			memcpy(musicData, fImage, fSz);
			Bgm* bgm = new Bgm(musicData, fSz);
			RETURN_ERRORABLE(bgm);
			*handle = bgm->Handle();

			return PSM_ERROR_NO_ERROR;
		}
		else {
			return PSM_ERROR_OUT_OF_MEMORY;
		}
	}

	int Bgm::ReleaseNative(int handle) {
		LOG_FUNCTION();
		
		if (Handles::IsValid(handle)) {
			Bgm* bgm = Handles::Get<Bgm>(handle);
			delete bgm;
		}

		return PSM_ERROR_NO_ERROR;
	}
	int Bgm::CreatePlayerNative(int handle, int* playerHandle) {
		LOG_FUNCTION();
		if (playerHandle == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (Handles::IsValid(handle)) {
			Bgm* bgm = Handles::Get<Bgm>(handle);
			BgmPlayer* player = BgmPlayer::Create(bgm);

			if (Handles::IsValid(player->Handle())) {
				*playerHandle = player->Handle();
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
