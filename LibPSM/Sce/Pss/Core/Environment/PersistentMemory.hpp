#ifndef LIB_PSS_PERSISTENTMEMORY_H
#define LIB_PSS_PERSISTENTMEMORY_H 1
#include <string>
#include <iostream>
#include <mono/mono.h>

namespace Sce::Pss::Core::Environment {
	class PersistentMemory {
	private:
		static uint8_t memoryBuffer[0x10000];
		static std::string pmDatFile;
		static int readPersistantMemory(uint8_t* persistantMemory, size_t persistantMemSize);
		static int writePersistantMemory(uint8_t* persistantMemory, size_t persistantMemSize);
	public:
		static int WriteNative(MonoArray* fileImage);
		static int ReadNative(MonoArray* fileImage);
		static int WritePersistantMemoryToDisk();
		static int ReadPersistantMemoryFromDisk();
	};
}
#endif
