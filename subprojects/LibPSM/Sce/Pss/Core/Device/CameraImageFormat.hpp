#ifndef LIB_PSS_CAMERAIMAGEFORMAT_H
#define LIB_PSS_CAMERAIMAGEFORMAT_H

namespace Sce::Pss::Core::Device {
	enum class CameraImageFormat : unsigned int {
		Rgb565 = 0,
		Rgba8888 = 1
	};
}

#endif