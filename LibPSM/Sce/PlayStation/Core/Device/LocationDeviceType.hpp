#ifndef LIB_PSM_LOCATIONDEVICETYPE_H
#define LIB_PSM_LOCATIONDEVICETYPE_H

namespace Sce::PlayStation::Core::Device {
	enum class LocationDeviceType : unsigned int {
		None = 0x00,
		Gps = 0x01,
		Wifi = 0x02,
		Cell3G = 0x04,
		Unknown = 0x80000000
	};
}

#endif