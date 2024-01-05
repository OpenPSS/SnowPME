#ifndef LIB_PSS_NETWORKINFORMATION_H
#define LIB_PSS_NETWORKINFORMATION_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::Pss::Core::Environment {
	class NetworkInformation {
	public:
		static int GetNetworkInterfaceTypeNative();
	};
}
#endif
