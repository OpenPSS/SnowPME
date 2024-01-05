#ifndef LIB_PSS_SOUNDSTATUS_H
#define LIB_PSS_SOUNDSTATUS_H

namespace Sce::Pss::Core::Audio {
	enum class SoundStatus : unsigned int {
		Stopped = 0,
		Playing = 1
	};
}

#endif