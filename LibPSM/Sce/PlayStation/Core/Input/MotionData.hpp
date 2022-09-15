#ifndef LIB_PSM_MOTIONDATA_H
#define LIB_PSM_MOTIONDATA_H
#include "../Vector3.hpp"
using namespace Sce::PlayStation::Core;
namespace Sce::PlayStation::Core::Input {
	typedef struct MotionData {
		bool Skip;
		Vector3 Acceleration;
		Vector3 AngularVelocity;
	} MotionData;
}

#endif