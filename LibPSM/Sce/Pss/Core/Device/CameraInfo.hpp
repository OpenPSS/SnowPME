#ifndef LIB_PSS_CAMERAINFO_H
#define LIB_PSS_CAMERAINFO_H
#include "CameraFacing.hpp"
#include "CameraSize.hpp"

namespace Sce::Pss::Core::Device {
	typedef struct CameraInfo {
		CameraFacing Facing;
		CameraSize* SupportedPreviewSizes;
		CameraSize* SupportedPictureSizes;
	} CameraInfo;
}

#endif