#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Environment/SystemEvents.hpp>
#include <LibShared.hpp>

using namespace Shared::Windowing;
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Environment;

namespace Sce::Pss::Core::Environment {

	Capture SystemEvents::state;

	int SystemEvents::CheckEvents(InternalData* internalData) {

		state = WindowControl::CaptureWindowState();

		internalData->QuitRequired = state.Closed;
		internalData->Minimized = state.Minmized;
		internalData->Restored = state.Restored;

		return PSM_ERROR_NO_ERROR;
	}

	int SystemEvents::CheckEventsNative(InternalData *data){
		Logger::Debug(__FUNCTION__);

		CheckEvents(data);

		return PSM_ERROR_NO_ERROR;
	}
}
