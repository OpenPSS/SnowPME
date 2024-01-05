#ifndef LIB_PSS_COMMONDIALOGSTATE_H
#define LIB_PSS_COMMONDIALOGSTATE_H

namespace Sce::Pss::Core::Environment {
	enum class CommonDialogState : unsigned int {
		None = 0,
		Running = 1,
		Finished = 2
	};

}

#endif