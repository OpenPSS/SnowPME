#ifndef LIB_PSS_BGMSTATUS_H
#define LIB_PSS_BGMSTATUS_H

namespace Sce::Pss::Core::Audio {
	enum class BgmStatus : unsigned int {
		Stopped = 0,
		Playing = 1,
		Paused = 2
	};
}

#endif