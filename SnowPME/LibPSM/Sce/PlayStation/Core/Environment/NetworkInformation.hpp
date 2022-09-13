#ifndef LIB_PSM_NETWORKINFORMATION_H
#define LIB_PSM_NETWORKINFORMATION_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Environment {
	class NetworkInformation {
	public:
		static int GetNetworkInterfaceTypeNative();
	};
}
#endif
