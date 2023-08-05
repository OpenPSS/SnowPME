#ifndef LIB_PSM_PERSISTENTMEMORY_H
#define LIB_PSM_PERSISTENTMEMORY_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {
	class PersistentMemory {
	public:
		static int WriteNative(uint8_t* fileImage);
		static int ReadNative(uint8_t* fileImage);
	};
}
#endif
