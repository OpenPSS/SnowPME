#ifndef LIB_PSM_THREAD_H
#define LIB_PSM_THREAD_H 1
#include <cstdint>

namespace Sce::Pss::Core::Threading {
	typedef uint64_t PsmThreadId;
	class Thread {
	public:
		static void SetMainThread(PsmThreadId threadId);
		static bool IsMainThread();
	};
}

#endif