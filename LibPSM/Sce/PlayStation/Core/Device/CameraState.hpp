#ifndef LIB_PSM_CAMERASTATE_H
#define LIB_PSM_CAMERASTATE_H

namespace Sce::PlayStation::Core::Device {
	enum class CameraState : unsigned int {
		Closed = 0,
		Stopped = 1,
		Running = 2,
		TakingPicture = 3
	};
}

#endif