#ifndef LIB_PSS_EDATASTREAM_H
#define LIB_PSS_EDATASTREAM_H 1
#include <Sce/Pss/Core/Io/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataHeader.hpp>
#include <Sce/Pss/Core/Io/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Crypto/AesCbc.hpp>
#include <Sce/Pss/Core/Io/IUnderlying.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>

#include <fstream>

#include <mono/mono.h>

#define PSSE_BLOCK_SIZE (0x8000)
#define PSSE_SIGNATURE_BLOCK_SIZE (0x80000)
#define PSSE_SIGNATURE_SIZE (0x400)

namespace Sce::Pss::Core::Io::Edata {
	class EdataStream : public IUnderlying, public PsmMutexObject<EdataStream> {
	private:
		std::unique_ptr<std::fstream> osHandle = nullptr;
		std::unique_ptr<Sce::Pss::Core::Crypto::AesCbc> aes = nullptr;

		bool psmDeveloperAssistant = false;

		EdataHeader header;

		uint8_t fileIv[0x10] = { 0 };
		uint8_t titleKey[0x10] = { 0 };

		std::vector<std::uint8_t> currentBlock = std::vector<std::uint8_t>();

		uint64_t position = 0;
		uint64_t block = 0;
		uint64_t totalFileSize = 0;
		uint64_t totalBlocks = 0;
		bool fileEncrypted = false;

		int blockPosition();
		int bytesLeftInBlock();
		uint64_t getRemainLength(uint64_t length, uint64_t totalRead);
		void decryptBlock(uint64_t blockNo);
		void rollIv(uint64_t blockNo, uint8_t blockIv[0x10]);
		
		uint64_t decryptedOffsetToAbsFileOffset(uint64_t offset);
		uint64_t absFileOffsetToDecryptedFileOffset(uint64_t offset);
		uint64_t getBlockAbsFileOffset(uint64_t blockNo);
		uint64_t getBlockDecryptedFileOffset(uint64_t blockNo);
		uint64_t getBlockIdForOffset(uint64_t offset);

	public:
		EdataList* EncryptedDataList = nullptr;

		EdataStream(const std::string& file, std::ios::openmode mode, PsmDrm* drm, EdataList* edata);
		~EdataStream();
		uint64_t Length();
		uint32_t Read(void* buffer, uint32_t length);
		uint32_t Write(void* buffer, uint32_t length);
		uint64_t Tell();
		int Seek(uint64_t position, ScePssFileSeekType_t pos);
		bool IsOpen();
		bool IsDirectory();
		bool IsEncrypted();
		void Close();
		void Flush();
		bool Verify();
	};
}

#endif