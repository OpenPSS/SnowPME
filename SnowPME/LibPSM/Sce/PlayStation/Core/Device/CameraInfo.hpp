#ifndef LIB_PSM_CAMERAINFO_H
#define LIB_PSM_CAMERAINFO_H
#include "CameraFacing.hpp"
#include "CameraSize.hpp"

namespace Sce::PlayStation::Core::Device {
	typedef struct CameraInfo {
		CameraFacing Facing;
		CameraSize* SupportedPreviewSizes;
		CameraSize* SupportedPictureSizes;
	} CameraInfo;
}

#endif