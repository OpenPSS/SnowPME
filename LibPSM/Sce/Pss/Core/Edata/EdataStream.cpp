#include <Sce/Pss/Core/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Crypto/Keys.hpp>
#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>
#include <LibShared.hpp>
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Crypto;

namespace Sce::Pss::Core::Edata {
	EdataStream::EdataStream(std::string file, char* gameKey) {
		memset(this->gameKey, 0x00, sizeof(EdataStream::gameKey));
		memset(this->fileIv, 0x00, sizeof(EdataStream::fileIv));
		memset(this->currentBlock, 0x00, sizeof(EdataStream::currentBlock));
		memset(&this->header, 0x00, sizeof(EdataHeader));

		// Copy the game key into this folder
		if (gameKey != nullptr)
			memcpy(this->gameKey, gameKey, sizeof(EdataStream::gameKey));

		this->osHandle = new std::fstream(file, std::ios::in | std::ios::binary);
		
		// if stream errors, return error code
		if (this->osHandle->fail()) {
			Logger::Error("Failed to open: " + file);
			this->SetError(PSM_ERROR_COMMON_IO);

			return;
		}

		// read psse header
		this->osHandle->read((char*)&this->header, sizeof(EdataStream::header));

		// check header is PSSE or PSME
		if (memcmp(this->header.Magic, "PSSE", sizeof(EdataHeader::Magic)) == 0 ||
			memcmp(this->header.Magic, "PSME", sizeof(EdataHeader::Magic)) == 0) {
			this->edataStream = true;

			// check version & type is not 1
			if (this->header.Version == 0x1 && this->header.PsseType != 0x1) {
				Logger::Error(file + " Has an invalid PSSE header.");
				this->SetError(PSM_ERROR_COMMON_IO);
				return;
			}

			// is runtime file?
			if (strncmp(this->header.ContentId, Keys::RuntimeContentId, sizeof(EdataHeader::ContentId)) == 0) {
				memcpy(this->gameKey, Keys::RuntimeGameKey, sizeof(Keys::RuntimeGameKey)); // copy the runtime game key as gamekey
			}
			
			this->psmDeveloperAssistant = (strnlen(this->header.ContentId, sizeof(EdataHeader::ContentId)) == 0);

			memcpy(this->fileIv, this->header.FileIv, sizeof(EdataStream::fileIv));
			CryptoLibrary::Aes128CbcDecrypt(this->psmDeveloperAssistant ? Keys::PsseHeaderKeyPsmDev : Keys::PsseHeaderKey, Keys::SequentialIv, (uint8_t*)this->fileIv, sizeof(EdataStream::fileIv));

		}
		this->edataStream = false;

	}
	EdataStream::~EdataStream() {
		delete this->osHandle;
	}
	int EdataStream::Read(char* buffer, size_t length) {
		return 1;
	}
	int EdataStream::Seek(int position, ScePssFileSeekType_t pos) {
		return 0;
	}
	void EdataStream::Close() {

	}
	bool EdataStream::Verify() {
		return true;
	}

}