#ifndef LIB_PSS_RESOURCES_H
#define LIB_PSS_RESOURCES_H 1

#include <string>
#include <iostream>
#include <cstdint>

namespace Sce::Pss::Core::Mono
{
	class Resources {
	public:
		static void ResourceLimitReachedCallback(int resourceType, uintptr_t value, int isSoft);
		static void ThreadsExhaustedCallback();
	};
}

#endif