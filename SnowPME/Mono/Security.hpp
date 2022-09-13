#ifndef SNOW_PME_MONO_SECURITY_H
#define SNOW_PME_MONO_SECURITY_H 1

#include <string>
#include <iostream>

using namespace std;
namespace SnowPME::Mono
{
	class Security {
	public:
		static int IsSecurityCriticalExempt(const char* exeFullPath);
	};

}

#endif