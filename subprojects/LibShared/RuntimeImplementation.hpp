#ifndef SHARED_RUNTIMEIMPLEMENTATION_H
#define SHARED_RUNTIMEIMPLEMENTATION_H 1
#include <cstdint>

namespace Shared {
	enum class RuntimeImplementation : uint32_t {
		PSVita = 0,
		Android = 1,
		Windows = 2
	};
}

#endif