#ifndef LIB_PSM_ACCOUNTINFORMATION_H
#define LIB_PSM_ACCOUNTINFORMATION_H 1
#include <mono/mono.h>

namespace Sce::PlayStation::Core::Services {
	class AccountInformation {
	public:
		static int GetUniqueID(MonoArray* id);
	};
}
#endif
