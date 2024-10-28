#include <Sce/Pss/Core/Event/PsmEvent.hpp>

namespace Sce::Pss::Core::Event {

	PsmEvent::PsmEvent(PsmEventType eventType) {
		this->EventType = eventType;
	}

	PsmEvent::PsmEvent() {
		this->EventType = PsmEventType::Unknown;
	}

}