#ifndef LIB_PSS_LOCATIONDATA_H
#define LIB_PSS_LOCATIONDATA_H
#include "LocationDeviceType.hpp"

namespace Sce::Pss::Core::Device {
	typedef struct LocationData {
		bool HasLatitude;
		double Latitude;
		bool HasLongitude;
		double Longitude;
		bool HasAltitude;
		double Altitude;
		bool HasSpeed;
		double Speed;
		bool HasTime;
		long Time;
		bool HasBearing;
		double Bearing;
		bool HasAccuracy;
		double Accuracy;
		LocationDeviceType DeviceType;
	} LocationData;
}

#endif