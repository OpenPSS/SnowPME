#ifndef LIB_PSM_CAMERAIMAGEFORMAT_H
#define LIB_PSM_CAMERAIMAGEFORMAT_H

namespace Sce::PlayStation::Core::Device {
	enum class CameraImageFormat : unsigned int {
		Rgb565 = 0,
		Rgba8888 = 1
	};
}

#endif