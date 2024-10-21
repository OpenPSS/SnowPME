#include <Sce/Pss/Core/Edata/EdataStream.hpp>

#include <Sce/Pss/Core/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Crypto/Keys.hpp>
#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>

#include <Sce/Pss/Core/Crypto/Md5Hash.hpp>
#include <Sce/Pss/Core/Edata/EdataHeader.hpp>
#include <Sce/Pss/Core/Crypto/AesCbc.hpp>

#include <Sce/Pss/Core/Edata/PsmDrm.hpp>
#include <LibShared.hpp>
#include <filesystem>
#include <errno.h>
#include <string.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Crypto;

namespace Sce::Pss::Core::Edata {

	static const int PsseBlockSize = 0x8000;
	static const int PsseSignatureBlockSize = 0x80000;
	static const int PsseSignatureSize = 0x400;

	void EdataStream::rollIv(uint64_t blockNo, uint8_t blockIv[0x10]) {
		memset(blockIv, 0x00, sizeof(EdataStream::fileIv));
		memcpy(blockIv, &blockNo, sizeof(uint64_t));
		for (int i = 0; i < sizeof(EdataStream::fileIv); i++)
			blockIv[i] = (blockIv[i] ^ this->fileIv[i]);
	}

	uint64_t EdataStream::getBlockAbsFileOffset(uint64_t blockNo) {
		uint64_t blockPosition = blockNo * PsseBlockSize;

		if (blockNo == 0) {
			blockPosition = sizeof(EdataHeader);
		}
		else if (blockPosition % PsseSignatureBlockSize == 0) {
			blockPosition += PsseSignatureSize;
		}

		return blockPosition;
	}

	uint64_t EdataStream::getBlockDecryptedFileOffset(uint64_t blockNo) {
		return this->absFileOffsetToDecryptedFileOffset(this->getBlockAbsFileOffset(blockNo));
	}

	uint64_t EdataStream::absFileOffsetToDecryptedFileOffset(uint64_t offset) {

		uint64_t totalSignatures = (offset / PsseSignatureBlockSize);

		uint64_t decryptedOffset = offset;
		decryptedOffset -= (PsseSignatureSize * totalSignatures);
		decryptedOffset -= sizeof(EdataHeader);

		return decryptedOffset;
	}
	uint64_t EdataStream::decryptedOffsetToAbsFileOffset(uint64_t offset) {
		uint64_t absfileLocation = offset;
		absfileLocation += sizeof(EdataHeader);

		uint64_t totalSignatures = (absfileLocation / PsseSignatureBlockSize);
		absfileLocation += (PsseSignatureSize * totalSignatures);

		return absfileLocation;
	}

	uint64_t EdataStream::getBlockIdForOffset(uint64_t offset) {
		uint64_t absFileOffset = this->decryptedOffsetToAbsFileOffset(offset);
		absFileOffset -= (absFileOffset % PsseBlockSize);
		return absFileOffset / PsseBlockSize;
	}

	void EdataStream::decryptBlock(uint64_t blockNo) {
		if (blockNo > this->totalBlocks) return;
		if (blockNo < 0) return;
		
		uint8_t iv[0x10];
		// generate the new iv
		this->rollIv(blockNo, iv);
		// set is as the iv in the aes context
		aes->SetIv(iv);

		this->block = blockNo;

		uint64_t blockPosition = blockNo * PsseBlockSize;
		size_t totalRead = PsseBlockSize;
		uint64_t trimTo = totalRead;

		// Handle special processing ...
		if (blockNo == 0) {  
			blockPosition = sizeof(EdataHeader);
			totalRead -= sizeof(EdataHeader);
			trimTo = totalRead;
		}
		else if (blockPosition % PsseSignatureBlockSize == 0) {
			blockPosition += PsseSignatureSize;
			totalRead -= PsseSignatureSize;
			trimTo = totalRead;
		}

		// total amount of bytes read so far
		uint64_t readAmount = ((blockPosition - sizeof(EdataHeader)) - (PsseSignatureSize * (blockPosition / PsseSignatureBlockSize)));

		if (blockNo >= this->totalBlocks) { // Is this the last block?
			totalRead = this->header.FileSize - readAmount;
			trimTo = totalRead;
			totalRead += ((CryptoLibrary::AesBlockSize)-(totalRead % (CryptoLibrary::AesBlockSize)));
		}

		// setup current block buffer
		this->currentBlock.resize(totalRead);
		this->osHandle->clear();
		this->osHandle->seekg(blockPosition, std::ios::beg);

		// decrypt block and copy to the currentBlock vector
		this->osHandle->read((char*)this->currentBlock.data(), totalRead);
		
		// decrypt the current block
		aes->Decrypt(this->currentBlock);

		if(this->currentBlock.size() != trimTo)
			this->currentBlock.resize(trimTo);

	}

	int EdataStream::blockPosition() {
		int blockPosition = (this->position - this->getBlockDecryptedFileOffset(this->block));

		if (blockPosition > this->currentBlock.size())
			blockPosition = this->currentBlock.size();

		if (blockPosition < 0)
			blockPosition = 0;

		return blockPosition;
	}

	int EdataStream::bytesLeftInBlock() {
		return this->currentBlock.size() - this->blockPosition();
	}
	size_t EdataStream::getRemainLength(size_t length, size_t totalRead) {
		return length - totalRead;
	}

	EdataStream::EdataStream(const std::string& file, std::ios::openmode mode, PsmDrm* drm, EdataList* edata) {
		memset(this->titleKey, 0x00, sizeof(EdataStream::titleKey));
		memset(this->fileIv, 0x00, sizeof(EdataStream::fileIv));

		this->EncryptedDataList = edata;

		// copy the titlekey into this object
		if(drm != nullptr)
			drm->GetTitleKey(this->titleKey);

		memset(&this->header, 0x00, sizeof(EdataHeader));
 

		if (std::filesystem::exists(file)) {
			this->totalFileSize = std::filesystem::file_size(file);
			this->totalBlocks = (this->totalFileSize / PsseBlockSize);
		}
		this->osHandle = new std::fstream(file, mode);

		// if stream errors, return error code

		if (this->osHandle->fail() || !this->osHandle->is_open()) {
			Logger::Error("Failed to open: \"" + file + "\": (" + std::to_string(errno) + ") " + strerror(errno));

			if (this->osHandle != nullptr) {
				delete this->osHandle;
				this->osHandle = nullptr;
			}

			switch (errno) {
			case EPERM:
				this->SetError(PSM_ERROR_ACCESS_DENIED);
				break;
			case ENOENT:
				this->SetError(PSM_ERROR_FILE_NOT_FOUND);
				break;
			case EEXIST:
				this->SetError(PSM_ERROR_ALREADY_EXISTS);
				break;
			default:
				this->SetError(PSM_ERROR_COMMON_IO);
				break;
			}

			return;

		}

		// handle psse ;
		if (this->EncryptedDataList == nullptr || this->EncryptedDataList->IsFileInEdata(file) && std::filesystem::exists(file)) {
			this->osHandle->read((char*)&this->header, sizeof(EdataStream::header));

			// check header is PSSE or PSME
			if (this->osHandle->gcount() >= sizeof(EdataHeader) &&
				memcmp(this->header.Magic, "PSSE", sizeof(EdataHeader::Magic)) == 0 ||
				memcmp(this->header.Magic, "PSME", sizeof(EdataHeader::Magic)) == 0) {

				this->FileEncrypted = true;

				// check version & type is not 1
				if (this->header.Version == 0x1 && this->header.PsseType != 0x1) {
					Logger::Error(file + " Has an invalid PSSE header.");

					if (this->osHandle != nullptr) {
						delete this->osHandle;
						this->osHandle = nullptr;
					}

					this->SetError(PSM_ERROR_COMMON_IO);
					return;
				}

				// is runtime file?
				if (strncmp(this->header.ContentId, Keys::RuntimeContentId.c_str(), sizeof(EdataHeader::ContentId)) == 0) {
					memcpy(this->titleKey, Keys::RuntimeTitleKey, sizeof(Keys::RuntimeTitleKey)); // copy the runtime game key as gamekey
				}

				// if no content id set then this is psm developer assistant application
				this->psmDeveloperAssistant = (strnlen(this->header.ContentId, sizeof(EdataHeader::ContentId)) == 0);
				memcpy(this->fileIv, this->header.FileIv, sizeof(EdataStream::fileIv));

				// decrypt the IV from the file header
				CryptoLibrary::Aes128CbcDecrypt(this->psmDeveloperAssistant ? Keys::PsseHeaderKeyPsmDev : Keys::PsseHeaderKey, Keys::SequentialIv, (uint8_t*)this->fileIv, sizeof(EdataStream::fileIv));
				this->aes = new AesCbc(this->titleKey, this->fileIv);

				// decrypt first block from the PSSE'd file
				decryptBlock(this->block);
				return;
			}
		}
			
		this->FileEncrypted = false;
		this->osHandle->clear();
		this->osHandle->seekg(0, std::ios::beg);
		return;
	}

	EdataStream::~EdataStream() {
		if (this->aes != nullptr) {
			delete aes;
		}

		if (this->osHandle != nullptr && this->osHandle->is_open()) {
			this->Close();
		}

		if (this->osHandle != nullptr) {
			delete this->osHandle;
			this->osHandle = nullptr;
		}
	}

	uint64_t EdataStream::Filesize() {
		if (this->FileEncrypted)
			return this->header.FileSize;
		else
			return this->totalFileSize;
	}

	int EdataStream::Read(char* buffer, size_t length) {
		if (this->FileEncrypted) {

			uint64_t blockNo = this->getBlockIdForOffset(this->position);
			if (this->block != blockNo) {
				this->decryptBlock(blockNo);
			}

			size_t totalRead = 0;
			if (length > this->getRemainLength(this->Filesize(), this->position))
				length = this->getRemainLength(this->Filesize(), this->position);
			if (length < 0)
				return 0;

			while (this->getRemainLength(length, totalRead) > this->bytesLeftInBlock()) {
				totalRead += this->Read(buffer + totalRead, this->bytesLeftInBlock());
			}

			if (this->getRemainLength(length, totalRead) <= bytesLeftInBlock()) {
				memcpy(buffer + totalRead, this->currentBlock.data(), this->getRemainLength(length, totalRead));

				this->position += this->getRemainLength(length, totalRead);

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
		if (this->FileEncrypted) {

			switch (pos) {
			case SCE_PSS_FILE_SEEK_TYPE_BEGIN:
				this->position = position;
				break;
			case SCE_PSS_FILE_SEEK_TYPE_CURRENT:
				this->position += position;
				break;
			case SCE_PSS_FILE_SEEK_TYPE_END:
				this->position = this->Filesize() - position;
				break;
			default:
				return PSM_ERROR_INVALID_PARAMETER;
			}
		}
		else{
			switch (pos) {
			case SCE_PSS_FILE_SEEK_TYPE_BEGIN:
				this->position = position;
				this->osHandle->clear();
				this->osHandle->seekg(position, std::ios::beg);
				break;
			case SCE_PSS_FILE_SEEK_TYPE_CURRENT:
				this->position += position;
				this->osHandle->clear();
				this->osHandle->seekg(position, std::ios::cur);
				break;
			case SCE_PSS_FILE_SEEK_TYPE_END:
				this->position = this->Filesize() - position;
				this->osHandle->clear();
				this->osHandle->seekg(position, std::ios::end);
				break;
			default:
				return PSM_ERROR_INVALID_PARAMETER;
			}
		}


		if (this->position > this->Filesize())
			this->position = this->Filesize();

		if (this->position < 0)
			this->position = 0;

 		if (this->FileEncrypted) {
			uint64_t blockNo = this->getBlockIdForOffset(this->position);
			if (this->block != blockNo) {
				this->decryptBlock(blockNo);
			}
		}

		return PSM_ERROR_NO_ERROR;
	}

	bool EdataStream::IsOpen() {
		return this->osHandle->is_open();
	}

	uint64_t EdataStream::Tell() {
		return this->position;
	}

	int EdataStream::Write(char* buffer, size_t length) {
		if (!this->FileEncrypted) {
			this->osHandle->write(buffer, length);
			this->position += length;
			return length;
		}
		return PSM_ERROR_WRITE_FAILED;
	}
	void EdataStream::Flush() {
		if (!this->FileEncrypted) {
			this->osHandle->flush();
		}
	}
	void EdataStream::Close() {
		if (this->FileEncrypted) {
			this->currentBlock.clear();
			this->osHandle->close();
		}
		else {
			this->osHandle->close();
		}

		if (this->osHandle != nullptr) {
			delete this->osHandle;
			this->osHandle = nullptr;
		}
	}
	bool EdataStream::Verify() {
		if (this->FileEncrypted) {
			uint64_t oldPosition = this->position;

			std::vector<uint8_t> data = std::vector<uint8_t>(this->Filesize());
			uint8_t gotMd5[CryptoLibrary::Md5HashSize];

			this->Read((char*)data.data(), this->Filesize());
			CryptoLibrary::Md5Sum(data.data(), data.size(), gotMd5);

			bool isValid = memcmp(this->header.Md5Hash, gotMd5, CryptoLibrary::Md5HashSize) == 0;

			this->Seek((int)oldPosition, SCE_PSS_FILE_SEEK_TYPE_BEGIN);
			return isValid;
		}
		else{
			return true;
		}
	}

}
