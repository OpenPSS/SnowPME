#ifndef SHARED_RUNFUNCTION_H
#define SHARED_RUNFUNCTION_H 1
#include <cstdint>

namespace Shared::Windowing {
	typedef struct RunFunction {
		uintptr_t (*functionPointer)(uintptr_t, uintptr_t, uintptr_t, uintptr_t) = 0;
		uintptr_t arg0 = 0;
		uintptr_t arg1 = 0;
		uintptr_t arg2 = 0;
		uintptr_t arg3 = 0;
	} RunFunction;
};


#endif