#include <Sce/Pss/Core/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Crypto/Keys.hpp>
#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>
#include <LibShared.hpp>
#include <filesystem>
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Crypto;

namespace Sce::Pss::Core::Edata {
	EdataStream::EdataStream(std::string file, char* gameKey) {
		memset(this->gameKey, 0x00, sizeof(EdataStream::gameKey));
		memset(this->fileIv, 0x00, sizeof(EdataStream::fileIv));

		// Copy the game key into this folder
		if (gameKey != nullptr)
			memcpy(this->gameKey, gameKey, sizeof(EdataStream::gameKey));

		if (std::filesystem::exists(file)) {
			this->totalFileSize = std::filesystem::file_size(file);
			this->totalBlocks = (this->totalFileSize / EdataStream::PsseBlockSize);

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
			if ( this->osHandle->gcount() >= sizeof(EdataHeader) && memcmp(this->header.Magic, "PSSE", sizeof(EdataHeader::Magic)) == 0 || memcmp(this->header.Magic, "PSME", sizeof(EdataHeader::Magic)) == 0) {

				this->encryptedFile = true;

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

				// if no content id set then this is psm developer assistant application
				this->psmDeveloperAssistant = (strnlen(this->header.ContentId, sizeof(EdataHeader::ContentId)) == 0);

				memcpy(this->fileIv, this->header.FileIv, sizeof(EdataStream::fileIv));
				CryptoLibrary::Aes128CbcDecrypt(this->psmDeveloperAssistant ? Keys::PsseHeaderKeyPsmDev : Keys::PsseHeaderKey, Keys::SequentialIv, (uint8_t*)this->fileIv, sizeof(EdataStream::fileIv));

				decryptBlock(this->block);
				return;
			}
			this->encryptedFile = false;
			this->osHandle->seekg(0, std::ios::beg);
		}
		else {
			this->SetError(PSM_ERROR_FILE_NOT_FOUND);
		}


	}
	EdataStream::~EdataStream() {
		if(this->osHandle != nullptr && this->osHandle->is_open())
			this->Close();
	}
	void EdataStream::rollIv(uint64_t blockNo, char blockIv[0x10]) {
		memset(blockIv, 0x00, sizeof(EdataStream::fileIv));
		memcpy(blockIv, &blockNo, sizeof(uint64_t));
		for (int i = 0; i < sizeof(EdataStream::fileIv); i++)
			blockIv[i] = (blockIv[i] ^ this->fileIv[i]);
	}


	void EdataStream::decryptBlock(uint64_t blockNo) {
		if (blockNo > this->totalBlocks) return;
		if (blockNo < 0) return;

		char iv[0x10];
		this->rollIv(blockNo, iv);

		this->block = blockNo;


		uint64_t blockPosition = blockNo * EdataStream::PsseBlockSize;
		size_t totalRead = EdataStream::PsseBlockSize;
		uint64_t trimTo = totalRead;

		// Handle special processing ...
		if (blockNo == 0) {  
			blockPosition = sizeof(EdataHeader);
			totalRead -= sizeof(EdataHeader);
			trimTo = totalRead;
		}
		else if (blockPosition % EdataStream::PsseSignatureBlockSize == 0) {
			blockPosition += EdataStream::PsseSignatureSize;
			totalRead -= EdataStream::PsseSignatureSize;
			trimTo = totalRead;
		}

		// total amount of bytes read so far
		uint64_t readAmount = ((blockPosition - sizeof(EdataHeader)) - (EdataStream::PsseSignatureSize * (blockPosition / EdataStream::PsseSignatureBlockSize)));

		if (blockNo >= this->totalBlocks) { // Is this the last block?
			totalRead = this->header.FileSize - readAmount;
			trimTo = totalRead;
			totalRead += ((CryptoLibrary::AesBlockSize)-(totalRead % (CryptoLibrary::AesBlockSize)));
		}

		// setup current block buffer
		this->currentBlock.resize(trimTo);
		this->osHandle->seekg(blockPosition, std::ios::beg);

		// decrypt block and copy to the currentBlock vector
		char* blk = new char[totalRead];
		this->osHandle->read(blk, totalRead);

		CryptoLibrary::Aes128CbcDecrypt((uint8_t*)this->gameKey, (uint8_t*)iv, (uint8_t*)blk, totalRead);
		memcpy(this->currentBlock.data(), blk, trimTo);
		
		delete[] blk;
		this->blockPosition = 0;
	}
	int EdataStream::bytesLeftInBlock() {
		return this->currentBlock.size() - this->blockPosition;
	}
	size_t EdataStream::getRemainLength(size_t length, size_t totalRead) {
		return length - totalRead;
	}
	uint64_t EdataStream::Filesize() {
		if (this->encryptedFile)
			return this->header.FileSize;
		else
			return this->totalFileSize;
	}

	int EdataStream::Read(char* buffer, size_t length) {
		if (this->encryptedFile) {
			size_t totalRead = 0;
			if (length > this->Filesize())
				length = this->Filesize();
			if (length < 0)
				return 0;

			while (this->getRemainLength(length, totalRead) > this->bytesLeftInBlock()) {
				totalRead += this->Read(buffer + totalRead, this->bytesLeftInBlock());
			}

			if (this->getRemainLength(length, totalRead) <= bytesLeftInBlock()) {
				memcpy(buffer + totalRead, this->currentBlock.data(), this->getRemainLength(length, totalRead));

				this->position += this->getRemainLength(length, totalRead);
				this->blockPosition += this->getRemainLength(length, totalRead);

				if (bytesLeftInBlock() <= 0) {
					this->decryptBlock(this->block + 1);
				}

				return length;
			}
		}
		else {
			this->osHandle->read(buffer, length);

			uint64_t read = this->osHandle->gcount();
			this->position += read;
			
			return (int)read;
		}
	}
	int EdataStream::Seek(int position, ScePssFileSeekType_t pos) {
		if (this->encryptedFile) {

		}
		else{
			switch (pos) {
			case SCE_PSS_FILE_SEEK_TYPE_BEGIN:
				this->position = position;
				this->osHandle->seekg(position, std::ios::beg);
				break;
			case SCE_PSS_FILE_SEEK_TYPE_CURRENT:
				this->position += position;
				this->osHandle->seekg(position, std::ios::cur);
				break;
			case SCE_PSS_FILE_SEEK_TYPE_END:
				this->position = this->totalFileSize - position;
				this->osHandle->seekg(position, std::ios::end);
				break;
			default:
				return PSM_ERROR_ERROR;
			}

			if (this->position > this->totalFileSize)
				this->position = this->totalFileSize;

			if (this->position < 0)
				this->position = 0;


			return PSM_ERROR_NO_ERROR;
		}
	}
	void EdataStream::Close() {
		if (this->encryptedFile) {
			this->currentBlock.clear();
			this->osHandle->close();
		}
		else {
			this->osHandle->close();
		}
		delete this->osHandle;
	}
	bool EdataStream::Verify() {
		if (!this->encryptedFile) {
			return true;
		}
	}

}