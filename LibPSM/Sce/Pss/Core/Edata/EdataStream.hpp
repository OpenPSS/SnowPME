#ifndef LIB_PSS_PSSE_STREAM_H
#define LIB_PSS_PSSE_STREAM_H 1
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Edata/EdataHeader.hpp>

#include <fstream>
#include <mono/mono.h>

namespace Sce::Pss::Core::Edata {
	

	class EdataStream : public PsmObject {
	private:
		static const int BlockSize = 0x8000;
		static const int SignatureBlockSize = 0x80000;
		static const int SignatureSize = 0x400;

		std::fstream* osHandle = nullptr;
		bool edataStream = false;
		bool psmDeveloperAssistant = false;
		char gameKey[0x10];
		char currentBlock[BlockSize];
		EdataHeader header;
		
		char fileIv[0x10];


		uint64_t position = 0;		
		size_t filesize = 0x00;
	public:
		EdataStream(std::string file, char gameKey[0x10]);
		~EdataStream();
		int Read(char* buffer, size_t length);
		int Seek(int position, ScePssFileSeekType_t pos);
		void Close();
		bool Verify();

	};
}

#endif