#ifndef LIB_PSM_NETWORKINFORMATION_H
#define LIB_PSM_NETWORKINFORMATION_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {
	class NetworkInformation {
	public:
		static int GetNetworkInterfaceTypeNative();
	};
}
#endif