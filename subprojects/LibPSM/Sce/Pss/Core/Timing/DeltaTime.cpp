#include <Sce/Pss/Core/Timing/DeltaTime.hpp>
#include <LibShared.hpp>

using namespace Shared::Windowing;

namespace Sce::Pss::Core::Timing {

	DeltaTime::DeltaTime(int minDelta) {
		this->minDelta = minDelta;
		this->lastTime = WindowControl::GetTime();
	}
	DeltaTime::~DeltaTime() {

	}
	uint64_t DeltaTime::CalculateDelta() {
		// get the current time .
		uint64_t currentTime = WindowControl::GetTime();
		// subtract current time from the last time.
		uint64_t deltaTime = currentTime - this->lastTime;
		// set the last time to the current time
		this->lastTime = currentTime;

		return deltaTime;
	}

	uint64_t DeltaTime::MinDelta() {
		return (1 / this->minDelta);
	}

}