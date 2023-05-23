#ifndef LIB_PSM_DELTATIME_H
#define LIB_PSM_DELTATIME_H 1

namespace Sce::Pss::Core::Timing {
	class DeltaTime{
	private:
		double minDelta;
		double lastTime;
	public:
		DeltaTime(int minDelta);
		~DeltaTime();

		double MinDelta();
		double CalculateDelta();
	};
}

#endif