#include <Sce/Pss/Core/Environment/SystemEvent.hpp>
#include <Sce/Pss/Core/Environment/SystemEvent.hpp>
#include <Sce/Pss/Core/Graphics/WindowSystemCallbacks.hpp>

#include <Sce/PlayStation/Core/Environment/InternalData.hpp>
#include <Sce/PlayStation/Core/Error.hpp>

#include <vector>
#include <LibShared.hpp>

using namespace Sce::PlayStation::Core::Environment;
using namespace Sce::Pss::Core::Graphics;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Environment {
	bool SystemEvent::lastMinimized = false;
	bool SystemEvent::lastQuit = false;
	bool SystemEvent::lastRestored = false;

	int SystemEvent::CheckEvents(InternalData* internalData) {

		WindowSystemCallbacks::PollEvents();

		// check minimized
		if (!SystemEvent::lastMinimized && WindowSystemCallbacks::IsMinimized()) {
			Logger::Debug("Minimize event set");
			internalData->Minimized = true;
			SystemEvent::lastMinimized = true;
		}
		else {
			internalData->Minimized = false;
		}

		// check quit
		if (!SystemEvent::lastQuit && WindowSystemCallbacks::IsClosed()) {
			Logger::Debug("Close event set");
			internalData->QuitRequired = true;
			SystemEvent::lastQuit = true;
		}
		else {
			internalData->QuitRequired = false;
		}

		// check restore
		if (SystemEvent::lastMinimized && !WindowSystemCallbacks::IsMinimized()) {
			Logger::Debug("Restore event set");
			internalData->Restored = true;
			SystemEvent::lastMinimized = false;
		}
		else {
			internalData->Restored = false;
		}

		return PSM_ERROR_NO_ERROR;
	}
}