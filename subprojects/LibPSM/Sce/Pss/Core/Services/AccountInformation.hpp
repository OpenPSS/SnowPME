#ifndef LIB_PSS_ACCOUNTINFORMATION_H
#define LIB_PSS_ACCOUNTINFORMATION_H 1

#include <mono/mono.h>

namespace Sce::Pss::Core::Services {
	class AccountInformation {
	public:
		static int GetUniqueID(MonoArray* id);
	};
}
#endif
