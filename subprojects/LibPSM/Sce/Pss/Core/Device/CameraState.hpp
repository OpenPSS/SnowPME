#ifndef LIB_PSS_CAMERASTATE_H
#define LIB_PSS_CAMERASTATE_H

namespace Sce::Pss::Core::Device {
	enum class CameraState : unsigned int {
		Closed = 0,
		Stopped = 1,
		Running = 2,
		TakingPicture = 3
	};
}

#endif