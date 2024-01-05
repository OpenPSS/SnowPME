#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Environment/SystemEvents.hpp>
#include <Sce/Pss/Core/Callback/WindowCallbacks.hpp>

#include <LibShared.hpp>
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Environment;
using namespace Sce::Pss::Core::Callback;

namespace Sce::Pss::Core::Environment {
	bool SystemEvents::lastMinimized = false;
	bool SystemEvents::lastQuit = false;
	bool SystemEvents::lastRestored = false;

	int SystemEvents::CheckEvents(InternalData* internalData) {

		WindowCallbacks::PollEvents();

		// check minimized
		if (!SystemEvents::lastMinimized && WindowCallbacks::IsMinimized()) {
			Logger::Debug("Minimize event set");
			internalData->Minimized = true;
			SystemEvents::lastMinimized = true;
		}
		else {
			internalData->Minimized = false;
		}

		// check quit
		if (!SystemEvents::lastQuit && WindowCallbacks::IsClosed()) {
			Logger::Debug("Close event set");
			internalData->QuitRequired = true;
			SystemEvents::lastQuit = true;
		}
		else {
			internalData->QuitRequired = false;
		}

		// check restore
		if (SystemEvents::lastMinimized && !WindowCallbacks::IsMinimized()) {
			Logger::Debug("Restore event set");
			internalData->Restored = true;
			SystemEvents::lastMinimized = false;
		}
		else {
			internalData->Restored = false;
		}

		return PSM_ERROR_NO_ERROR;
	}

	int SystemEvents::CheckEventsNative(InternalData *data){
		Logger::Debug(__FUNCTION__);

		CheckEvents(data);

		return PSM_ERROR_NO_ERROR;
	}
}
