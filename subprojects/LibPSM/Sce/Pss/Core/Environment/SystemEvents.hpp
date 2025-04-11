#ifndef LIB_PSS_SYSTEMEVENTS_H
#define LIB_PSS_SYSTEMEVENTS_H 1
#include <Sce/Pss/Core/Environment/InternalData.hpp>


namespace Sce::Pss::Core::Environment {

	class SystemEvents {
	private:
		static bool lastQuit;
		static bool lastMinimized;
		static bool lastRestored;
	public:
		static int CheckEvents(Sce::Pss::Core::Environment::InternalData* internalData);
		static int CheckEventsNative(InternalData *data);
	};
}
#endif
