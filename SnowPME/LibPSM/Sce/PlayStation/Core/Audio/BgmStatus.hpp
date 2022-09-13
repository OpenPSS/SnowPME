#ifndef LIB_PSM_BGMSTATUS_H
#define LIB_PSM_BGMSTATUS_H

namespace Sce::PlayStation::Core::Audio {
	enum class BgmStatus : unsigned int {
		Stopped = 0,
		Playing = 1,
		Paused = 2
	};
}

#endif