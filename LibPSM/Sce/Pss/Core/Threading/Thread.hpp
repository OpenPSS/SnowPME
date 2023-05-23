#ifndef LIB_PSM_THREAD_H
#define LIB_PSM_THREAD_H 1
#include <vector>

namespace Sce::Pss::Core::Threading {
	class Thread {
	private:
		static uint64_t mainThreadId;
	public:
		static void SetMainThread(uint64_t threadId);
		static bool IsMainThread();
		static uint64_t CurrentThreadId();
		static void Sleep(double time);
	};
}

#endif