#ifndef LIB_PSM_TOUCHSTATUS_H
#define LIB_PSM_TOUCHSTATUS_H

namespace Sce::PlayStation::Core::Input {
	enum class TouchStatus : unsigned int {
		None = 0,
		Down = 1,
		Up = 2,
		Move = 3,
		Canceled
	};
}

#endif