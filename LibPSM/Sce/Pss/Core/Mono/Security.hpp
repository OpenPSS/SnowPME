#ifndef LIB_PSM_SECURITY_H
#define LIB_PSM_SECURITY_H 1

#include <string>
#include <iostream>

namespace Sce::Pss::Core::Mono
{
	class Security {
	public:
		static int IsSecurityCriticalExempt(const char* exeFullPath);
	};
}

#endif