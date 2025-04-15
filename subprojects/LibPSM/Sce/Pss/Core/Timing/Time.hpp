#ifndef LIB_PSS_TIME_H
#define LIB_PSS_TIME_H 1
#include <cstdint>

#define VITA_TIME_EPOCH (0xFFFFFFF1886E0CC8ull)

namespace Sce::Pss::Core::Timing {
	class Time {
	public:
		static uint64_t scePssTimeGetMicroTickCount();
	};
}

#endif