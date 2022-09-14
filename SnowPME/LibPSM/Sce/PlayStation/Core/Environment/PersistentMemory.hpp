#ifndef LIB_PSM_PERSISTENTMEMORY_H
#define LIB_PSM_PERSISTENTMEMORY_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {
	class PersistentMemory {
	public:
		static int WriteNative(std::byte* fileImage);
		static int ReadNative(std::byte* fileImage);
	};
}
#endif
