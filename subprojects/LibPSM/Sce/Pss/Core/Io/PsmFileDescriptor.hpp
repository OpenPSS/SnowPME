#ifndef LIB_PSS_PSMFILEDESCRIPTOR_H
#define LIB_PSS_PSMFILEDESCRIPTOR_H 1
#include <Sce/Pss/Core/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Io/DirectoryIterator.hpp>
#include <iostream>
#include <mono/mono.h>


namespace Sce::Pss::Core::Io {
	typedef struct PsmFileDescriptor {
		bool opened = false;
		bool rw = false;
		bool directory = false;
		bool encrypted = false;
		bool emulated = false;
		uint32_t failReason = 0;
		uint32_t emulatedFilePosition = 0;
		ScePssFileOpenFlag_t flags = ScePssFileOpenFlag_t();
		std::ios_base::openmode iflags = std::ios_base::openmode();
		std::string sandboxPath = "";
		std::string realPath = "";

		Edata::EdataStream* edataStream = nullptr;
		DirectoryIterator* directoryFd = nullptr;
	} PsmFileDescriptor;
}

#endif