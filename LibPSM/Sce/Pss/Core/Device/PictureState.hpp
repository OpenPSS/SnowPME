#ifndef LIB_PSS_PICTURESTATE_H
#define LIB_PSS_PICTURESTATE_H

namespace Sce::Pss::Core::Device {
	enum class PictureState : int {
		Idle = 0,
		Running = 1,
		Finishied = 2,
		Failed = -1
	};
}

#endif