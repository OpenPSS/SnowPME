#ifndef LIB_PSS_LOCATION_H
#define LIB_PSS_LOCATION_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include "LocationData.hpp"



namespace Sce::Pss::Core::Device {
	class Location {
	public:
		static int StartNative();
		static int StopNative();
		static int GetDataNative(LocationData *locationData);
		static int GetEnableDevicesNative();
	};
}
#endif
