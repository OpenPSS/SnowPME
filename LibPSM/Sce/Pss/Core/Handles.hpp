#ifndef LIB_PSM_HANDLES_H
#define LIB_PSM_HANDLES_H 1
#include <cstdint>

#define MAX_HANDLES (0x100000)

namespace Sce::Pss::Core {
	typedef int PsmHandle;
	class Handles {
	private:
		static void init();
		static bool handleValid(PsmHandle handle);
	public:
		static PsmHandle CreateHandle(uintptr_t address);
		static uintptr_t GetHandle(PsmHandle handle);
		static void DeleteHandle(PsmHandle handle);
	};
}

#endif