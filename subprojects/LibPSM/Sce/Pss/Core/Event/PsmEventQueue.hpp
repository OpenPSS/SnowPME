#ifndef LIB_PSS_PSMEVENTQUEUE_H
#define LIB_PSS_PSMEVENTQUEUE_H 1
#include <Sce/Pss/Core/Event/PsmEvent.hpp>
#include <Sce/Pss/Core/Event/PsmEventType.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <queue>
#include <mutex>

namespace Sce::Pss::Core::Event {
	class PsmEventQueue : public PsmMutexObject<PsmEventQueue> {
	private:
		std::queue<PsmEvent*> evtQueue;
	public:
		static PsmEventQueue IncomingEventQueue;
		static PsmEventQueue OutgoingEventQueue;
		
		PsmEventQueue();
		~PsmEventQueue();

		void Push(PsmEvent* evt);
		PsmEvent* Pop();
	};
}

#endif