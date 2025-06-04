#ifndef LIB_PSS_PERSISTENTMEMORY_H
#define LIB_PSS_PERSISTENTMEMORY_H 1
#include <string>
#include <iostream>

#include <mono/mono.h>

#define PM_DAT_FILE (char*)("/System/pm.dat")
namespace Sce::Pss::Core::Environment {
	class PersistentMemory {
	private:
		static uint8_t memoryBuffer[0x10000];
	public:
		static int WriteNative(MonoArray* fileImage);
		static int ReadNative(MonoArray* fileImage);
		static int Read(uint8_t* persistantMemory, size_t persistantMemSize);
		static int Write(uint8_t* persistantMemory, size_t persistantMemSize);
		static int Flush();
		static int Initalize();
		static int Terminate();
	};
}
#endif
