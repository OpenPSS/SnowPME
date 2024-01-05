#ifndef LIB_PSS_MOTION_H
#define LIB_PSS_MOTION_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include "MotionData.hpp"


namespace Sce::Pss::Core::Input {
	class Motion {
	public:
		static int GetDataNative(int deviceIndex, MotionData *gamePadData);
	};
}
#endif
