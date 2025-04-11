#ifndef LIB_PSS_PSMEVENT_H
#define LIB_PSS_PSMEVENT_H 1
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Event/PsmEventType.hpp>
#include <string>
#include <cstdint>

namespace Sce::Pss::Core::Event {
	class PsmEvent : public PsmObject<PsmEvent> {
	public:
		PsmEventType EventType = PsmEventType::Unknown;
		PsmEvent(PsmEventType eventType);
		PsmEvent();
	};
}

#endif