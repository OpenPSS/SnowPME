#include <Sce/Pss/Core/Event/PsmEventQueue.hpp>
#include <Sce/Pss/Core/Event/PsmEvent.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <mutex>
#include <queue>
#include <thread>

#include <LibShared.hpp>
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Event {
	PsmEventQueue PsmEventQueue::IncomingEventQueue;
	PsmEventQueue PsmEventQueue::OutgoingEventQueue;

	void PsmEventQueue::Push(PsmEvent* evt) {
		std::scoped_lock<std::mutex> lock(evtLock);
		Logger::Debug(__FUNCTION__);
		evtQueue.push(evt);
	}
	PsmEvent* PsmEventQueue::Pop() {
		std::scoped_lock<std::mutex> lock(evtLock);
		Logger::Debug(__FUNCTION__);

		while (evtQueue.empty()) { Thread::Sleep(10.0); }
		PsmEvent* evt = evtQueue.front();
		evtQueue.pop();

		return evt;
	}

	PsmEventQueue::~PsmEventQueue() {
		std::scoped_lock<std::mutex> lock(evtLock);

		for (; !evtQueue.empty(); evtQueue.pop())
			delete evtQueue.front();

	}
}