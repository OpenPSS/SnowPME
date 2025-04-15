#include <Sce/Pss/Core/Timing/Time.hpp>
#include <chrono>

namespace Sce::Pss::Core::Timing {
	uint64_t Time::scePssTimeGetMicroTickCount() {
		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point vitaEpoch = std::chrono::system_clock::from_time_t(VITA_TIME_EPOCH);
		std::chrono::microseconds timeSinceVitaEpoch = std::chrono::duration_cast<std::chrono::microseconds>(timeNow - vitaEpoch);

		return timeSinceVitaEpoch.count();
	}
}