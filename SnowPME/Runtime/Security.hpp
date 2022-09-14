#ifndef SNOW_PME_MONO_SECURITY_H
#define SNOW_PME_MONO_SECURITY_H 1

#include <string>
#include <iostream>


namespace SnowPME::Runtime
{
	class Security {
	public:
		static int IsSecurityCriticalExempt(const char* exeFullPath);
	};

}

#endif