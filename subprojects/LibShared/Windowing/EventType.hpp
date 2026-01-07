#ifndef SHARED_EVENTTYPE_H
#define SHARED_EVENTTYPE_H 1

#include <vector>
#include <cstdint>
#include <string>

namespace Shared::Windowing {

	enum class EventType : uint32_t{
		None,
		Capture,
		RunFunction
	};

}


#endif