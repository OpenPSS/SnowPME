#ifndef LIB_PSS_PSMEVENTQUEUE_H
#define LIB_PSS_PSMEVENTQUEUE_H 1
#include <Sce/Pss/Core/Event/PsmEvent.hpp>
#include <Sce/Pss/Core/Event/PsmEventType.hpp>
#include <queue>
#include <mutex>

namespace Sce::Pss::Core::Event {
	class PsmEventQueue {
	private:
		std::queue<PsmEvent*> evtQueue;
		std::mutex evtLock;
	public:
		static PsmEventQueue IncomingEventQueue;
		static PsmEventQueue OutgoingEventQueue;

		void Push(PsmEvent* evt);
		PsmEvent* Pop();
		~PsmEventQueue();
	};
}

#endif