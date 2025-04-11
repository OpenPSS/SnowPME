#ifndef LIB_PSS_SYSTEMMEMORY_H
#define LIB_PSS_SYSTEMMEMORY_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::Pss::Core::Environment {
	class SystemMemory {
	public:
		static int GetMemoryUsage(bool details);
	};
}
#endif
