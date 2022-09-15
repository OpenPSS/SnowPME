#ifndef LIB_PSM_SYSTEMMEMORY_H
#define LIB_PSM_SYSTEMMEMORY_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {
	class SystemMemory {
	public:
		static int GetMemoryUsage(bool details);
	};
}
#endif
