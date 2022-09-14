#ifndef LIB_PSM_ACCOUNTINFORMATION_H
#define LIB_PSM_ACCOUNTINFORMATION_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Services {
	class AccountInformation {
	public:
		static int GetUniqueID(std::byte* id);
	};
}
#endif
