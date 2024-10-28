#ifndef LIB_PSS_PSMEVENTTYPE_H
#define LIB_PSS_PSMEVENTTYPE_H 1
#include <cstdint>

namespace Sce::Pss::Core::Event {
	enum class PsmEventType : uint32_t {
		Unknown,
		SwapBuffers,
		PollEvents
	};
}

#endif