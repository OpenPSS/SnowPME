#ifndef LIB_PSM_PICTURESTATE_H
#define LIB_PSM_PICTURESTATE_H

namespace Sce::PlayStation::Core::Device {
	enum class PictureState : int {
		Idle = 0,
		Running = 1,
		Finishied = 2,
		Failed = -1
	};
}

#endif