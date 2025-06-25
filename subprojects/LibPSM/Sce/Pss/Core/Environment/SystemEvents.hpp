#ifndef LIB_PSS_SYSTEMEVENTS_H
#define LIB_PSS_SYSTEMEVENTS_H 1
#include <Sce/Pss/Core/Environment/InternalData.hpp>
#include <LibShared.hpp>

namespace Sce::Pss::Core::Environment {

	class SystemEvents {
	private:
		static Shared::Windowing::Capture state;
	public:
		static int CheckEvents(InternalData* internalData);
		static int CheckEventsNative(InternalData *data);
	};
}
#endif
