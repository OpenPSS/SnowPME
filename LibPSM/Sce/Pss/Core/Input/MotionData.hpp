#ifndef LIB_PSS_MOTIONDATA_H
#define LIB_PSS_MOTIONDATA_H
#include "../Vector3.hpp"
using namespace Sce::Pss::Core;
namespace Sce::Pss::Core::Input {
	typedef struct MotionData {
		bool Skip;
		Vector3 Acceleration;
		Vector3 AngularVelocity;
	} MotionData;
}

#endif