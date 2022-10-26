#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <LibSnowPME.hpp>

using namespace SnowPME::Util;
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