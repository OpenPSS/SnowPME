#ifndef LIB_PSM_SYSTEMMEMORY_H
#define LIB_PSM_SYSTEMMEMORY_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Environment {
	class SystemMemory {
	public:
		static int GetMemoryUsage(bool details);
	};
}
#endif
