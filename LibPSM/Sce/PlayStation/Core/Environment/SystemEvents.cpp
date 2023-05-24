#include <Sce/PlayStation/Core/Error.hpp>
#include <Sce/PlayStation/Core/Environment/SystemEvents.hpp>
#include <Sce/Pss/Core/Environment/SystemEvent.hpp>
#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::PlayStation::Core::Environment {
	int SystemEvents::CheckEventsNative(InternalData *data){
		Logger::Debug(__FUNCTION__);

		Sce::Pss::Core::Environment::SystemEvent::CheckEvents(data);

		return PSM_ERROR_NO_ERROR;
	}
}
