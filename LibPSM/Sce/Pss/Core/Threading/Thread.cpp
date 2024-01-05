#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>

#include <chrono>
#include <thread>

namespace Sce::Pss::Core::Threading {
	uint64_t Thread::mainThreadId = NULL;

	uint64_t Thread::CurrentThreadId() {
		return std::hash<std::thread::id>{}(std::this_thread::get_id());
	}

	bool Thread::IsMainThread() {
		if (mainThreadId == Thread::CurrentThreadId()) {
			return true;
		}
		else {
			return false;
		}
	}
	
	void Thread::Sleep(double time) {
		uint64_t microseconds = (uint64_t)(time * 1000000.0);
		std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
	}

	void Thread::SetMainThread() {
		mainThreadId = Thread::CurrentThreadId();
	}
	void Thread::SetMainThread(uint64_t threadId) {
		mainThreadId = threadId;
	}

}