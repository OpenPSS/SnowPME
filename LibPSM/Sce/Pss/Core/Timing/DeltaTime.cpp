#include <Sce/Pss/Core/Callback/WindowCallbacks.hpp>
#include <Sce/Pss/Core/Timing/DeltaTime.hpp>
using namespace Sce::Pss::Core::Callback;

namespace Sce::Pss::Core::Timing {
	DeltaTime::DeltaTime(int minDelta) {
		this->minDelta = minDelta;
		this->lastTime = WindowCallbacks::GetTime();
	}
	DeltaTime::~DeltaTime() {

	}
	double DeltaTime::CalculateDelta() {
		// get the current time .
		double currentTime = WindowCallbacks::GetTime();
		// subtract current time from the last time.
		double deltaTime = currentTime - this->lastTime;
		// set the last time to the current time
		this->lastTime = currentTime;

		return deltaTime;
	}

	double DeltaTime::MinDelta() {
		return (1 / this->minDelta);
	}

}