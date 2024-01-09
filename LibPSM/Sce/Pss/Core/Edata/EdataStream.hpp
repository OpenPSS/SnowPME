#ifndef LIB_PSS_PSSE_STREAM_H
#define LIB_PSS_PSSE_STREAM_H 1
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Edata/EdataHeader.hpp>

#include <fstream>
#include <mono/mono.h>

namespace Sce::Pss::Core::Edata {
	

	class EdataStream : public PsmObject {
	private:
		static const int PsseBlockSize = 0x8000;
		static const int PsseSignatureBlockSize = 0x80000;
		static const int PsseSignatureSize = 0x400;

		std::fstream* osHandle = nullptr;
		bool encryptedFile = false;
		bool psmDeveloperAssistant = false;
		char gameKey[0x10];
		EdataHeader header;
		char fileIv[0x10];

		std::vector<std::byte> currentBlock = std::vector<std::byte>();

		uint32_t blockPosition = 0;
		uint64_t position = 0;
		
		uint64_t block = 0;
		uint64_t totalFileSize = 0;
		size_t totalBlocks = 0;

		int bytesLeftInBlock();
		size_t getRemainLength(size_t length, size_t totalRead);

		void decryptBlock(uint64_t blockNo);
		void rollIv(uint64_t blockNo, char blockIv[0x10]);
	public:
		EdataStream(std::string file, char gameKey[0x10]);
		~EdataStream();
		uint64_t Filesize();
		int Read(char* buffer, size_t length);
		int Seek(int position, ScePssFileSeekType_t pos);
		void Close();
		bool Verify();

	};
}

#endif