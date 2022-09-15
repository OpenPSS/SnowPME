#ifndef LIB_PSM_SOUNDSTATUS_H
#define LIB_PSM_SOUNDSTATUS_H

namespace Sce::PlayStation::Core::Audio {
	enum class SoundStatus : unsigned int {
		Stopped = 0,
		Playing = 1
	};
}

#endif