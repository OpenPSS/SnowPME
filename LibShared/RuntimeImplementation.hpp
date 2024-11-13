#ifndef SHARED_RUNTIMEIMPLEMENTATION_H
#define SHARED_RUNTIMEIMPLEMENTATION_H 1

namespace Shared {
	typedef enum class RuntimeImplementation : unsigned int {
		PSVita = 0,
		Android = 1,
		Windows = 2
	} RuntimeImplementation;
}

#endif