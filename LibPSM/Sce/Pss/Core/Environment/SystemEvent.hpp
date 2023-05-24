#ifndef LIB_PSS_SYSTEMEVENTS_H
#define LIB_PSS_SYSTEMEVENTS_H 1
#include <Sce/PlayStation/Core/Environment/InternalData.hpp>

namespace Sce::Pss::Core::Environment {
	class SystemEvent {
	private:
		static bool lastQuit;
		static bool lastMinimized;
		static bool lastRestored;
	public:
		static int CheckEvents(Sce::PlayStation::Core::Environment::InternalData* internalData);
	};
}

#endif