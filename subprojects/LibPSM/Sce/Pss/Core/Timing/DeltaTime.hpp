#ifndef LIB_PSS_DELTATIME_H
#define LIB_PSS_DELTATIME_H 1

#include <cstdint>

namespace Sce::Pss::Core::Timing {
	class DeltaTime{
	private:
		uint64_t minDelta;
		uint64_t lastTime;
	public:
		DeltaTime(int minDelta);
		~DeltaTime();

		uint64_t MinDelta();
		uint64_t CalculateDelta();
	};
}

#endif