#ifndef LIB_PSM_COMMONDIALOGRESULT_H
#define LIB_PSM_COMMONDIALOGRESULT_H 1

namespace Sce::PlayStation::Core::Environment {
	enum class CommonDialogResult : unsigned int {
		OK = 0,
		Canceled = 1,
		Aborted = 2,
		Error = 3
	};
}

#endif