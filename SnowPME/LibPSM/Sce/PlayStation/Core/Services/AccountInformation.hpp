#ifndef LIB_PSM_ACCOUNTINFORMATION_H
#define LIB_PSM_ACCOUNTINFORMATION_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Services {
	class AccountInformation {
	public:
		static int GetUniqueID(byte* id);
	};
}
#endif
