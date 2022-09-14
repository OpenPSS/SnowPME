#ifndef SNOW_PME_MONO_RESOURCES_H
#define SNOW_PME_MONO_RESOURCES_H 1

#include <string>
#include <iostream>


namespace SnowPME::Runtime
{
	class Resources {
	public:
		static void ResourceLimitReachedCallback(int resourceType, uintptr_t value, int isSoft);
		static void ThreadsExhaustedCallback();
	};
}

#endif