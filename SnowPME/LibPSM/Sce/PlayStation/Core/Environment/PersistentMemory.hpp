#ifndef LIB_PSM_PERSISTENTMEMORY_H
#define LIB_PSM_PERSISTENTMEMORY_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Environment {
	class PersistentMemory {
	public:
		static int WriteNative(byte* fileImage);
		static int ReadNative(byte* fileImage);
	};
}
#endif
