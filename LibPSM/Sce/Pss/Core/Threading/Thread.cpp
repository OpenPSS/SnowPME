#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/PlatformSpecific.hpp>

namespace Sce::Pss::Core::Threading {

	static PsmThreadId mainThreadId;

	bool Thread::IsMainThread() {
		if (mainThreadId == PlatformSpecific::CurrentThreadId()) {
			return true;
		}
		else {
			return false;
		}
	}

	void Thread::SetMainThread(PsmThreadId threadId) {
		mainThreadId = threadId;
	}

}