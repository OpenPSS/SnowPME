#ifndef LIB_PSS_HANDLES_H
#define LIB_PSS_HANDLES_H 1
#include <cstdint>

namespace Sce::Pss::Core {
	typedef uint32_t PsmHandle;
	class Handles {
	private:
		static void init();		
	public:
		static const PsmHandle NoHandle = NULL;
		static const PsmHandle MinHandle = 0x1;
		static const PsmHandle MaxHandle = 0x500000;
		static bool IsValid(PsmHandle handle);
		static PsmHandle CreateHandle(uintptr_t address);
		static uintptr_t GetHandle(PsmHandle handle);
		static void DeleteHandle(PsmHandle handle);
	};
}

#endif