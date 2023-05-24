#ifndef LIB_PSM_SYSTEMEVENTS_H
#define LIB_PSM_SYSTEMEVENTS_H 1
#include <Sce/PlayStation/Core/Environment/InternalData.hpp>


namespace Sce::PlayStation::Core::Environment {

	class SystemEvents {
	public:
		static int CheckEventsNative(InternalData *data);
	};
}
#endif
