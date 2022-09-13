#ifndef LIB_PSM_MOTION_H
#define LIB_PSM_MOTION_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "MotionData.hpp"
using namespace std;

namespace Sce::PlayStation::Core::Input {
	class Motion {
	public:
		static int GetDataNative(int deviceIndex, MotionData *gamePadData);
	};
}
#endif
