#ifndef SNOW_PME_MONO_RESOURCES_H
#define SNOW_PME_MONO_RESOURCES_H 1

#include <string>
#include <iostream>

using namespace std;
namespace SnowPME::Mono
{
	class Resources {
	public:
		static void ResourceLimitReachedCallback(int resourceType, uintptr_t value, int isSoft);
		static void ThreadsExhaustedCallback();
	};
}

#endif