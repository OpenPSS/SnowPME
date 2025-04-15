#include <Sce/Pss/Core/Event/PsmEventQueue.hpp>
#include <Sce/Pss/Core/Event/PsmEvent.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>

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
		LOCK_GUARD();

		this->evtQueue.push(evt);
	}
	PsmEvent* PsmEventQueue::Pop() {
		LOCK_GUARD();

		while (this->evtQueue.empty()) { return nullptr; }
		PsmEvent* evt = this->evtQueue.front();
		this->evtQueue.pop();

		return evt;
	}

	PsmEventQueue::PsmEventQueue() {

	}

	PsmEventQueue::~PsmEventQueue() {
		LOCK_GUARD();
		size_t queueSz = this->evtQueue.size();
		
		for (int i = 0; i < queueSz; i++) {
			PsmEvent* evt = this->evtQueue.front();
			if (evt != nullptr) delete evt;
			this->evtQueue.pop();
		}
	}

}