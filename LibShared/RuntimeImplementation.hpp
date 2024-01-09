#ifndef SHARED_RUNTIMEIMPLEMENTATION_H
#define SHARED_RUNTIMEIMPLEMENTATION_H 1

namespace Shared {
	typedef enum class RuntimeImplementation : unsigned int {
		Android,
		PSVita,
		Windows
	} RuntimeImplementation;
}

#endif