#ifndef LIB_PSS_HANDLES_H
#define LIB_PSS_HANDLES_H 1
#include <map>
#include <cstddef>
#include <stdint.h>

namespace Sce::Pss::Core::System {
	class Handles {
	private:
		static void init();		
	public:
		static const int NoHandle = NULL;
		static const int MinHandle = 0x1;
		static const int MaxHandle = 0x500000;
		static bool IsValid(int handle);
		static int CreateHandle(uintptr_t address);
		static uintptr_t GetHandle(int handle);
		static void DeleteHandle(int handle);
	};
}

#endif
