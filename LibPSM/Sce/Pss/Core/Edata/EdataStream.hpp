#ifndef LIB_PSS_EDATASTREAM_H
#define LIB_PSS_EDATASTREAM_H 1
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Edata/EdataHeader.hpp>
#include <Sce/Pss/Core/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Crypto/AesCbc.hpp>

#include <fstream>
#include <mono/mono.h>

namespace Sce::Pss::Core::Edata {
	class EdataStream : public PsmObject {
	private:
		std::fstream* osHandle = nullptr;
		Sce::Pss::Core::Crypto::AesCbc* aes = nullptr;

		bool psmDeveloperAssistant = false;

		EdataHeader header;

		uint8_t fileIv[0x10];
		uint8_t titleKey[0x10];

		std::vector<std::uint8_t> currentBlock = std::vector<std::uint8_t>();

		uint64_t position = 0;
		
		uint64_t block = 0;
		uint64_t totalFileSize = 0;
		size_t totalBlocks = 0;

		int blockPosition();
		int bytesLeftInBlock();
		size_t getRemainLength(size_t length, size_t totalRead);
		void decryptBlock(uint64_t blockNo);
		void getNewBlockIfDifferent(uint64_t blockNo);
		void rollIv(uint64_t blockNo, uint8_t blockIv[0x10]);
		
		uint64_t decryptedOffsetToAbsFileOffset(uint64_t offset);
		uint64_t absFileOffsetToDecryptedFileOffset(uint64_t offset);
		uint64_t getBlockAbsFileOffset(uint64_t blockNo);
		uint64_t getBlockDecryptedFileOffset(uint64_t blockNo);

		uint64_t getBlockIdForOffset(uint64_t offset);

		

	public:

		bool FileEncrypted = false;
		EdataList* EncryptedDataList = nullptr;

		EdataStream(std::string file, std::ios::openmode mode, PsmDrm* drm, EdataList* edata);
		~EdataStream();
		uint64_t Filesize();
		int Read(char* buffer, size_t length);
		int Write(char* buffer, size_t length);
		int Seek(int position, ScePssFileSeekType_t pos);
		bool IsOpen();
		void Close();
		bool Verify();
		void Flush();
		uint64_t Tell();
	};
}

#endif