#ifndef LIB_PSM_COMMONDIALOGSTATE_H
#define LIB_PSM_COMMONDIALOGSTATE_H

namespace Sce::PlayStation::Core::Environment {
	enum class CommonDialogState : unsigned int {
		None = 0,
		Running = 1,
		Finished = 2
	};
}

#endif