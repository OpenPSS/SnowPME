#ifndef LIB_PSS_COMMONDIALOGRESULT_H
#define LIB_PSS_COMMONDIALOGRESULT_H 1

namespace Sce::Pss::Core::Environment {
	enum class CommonDialogResult : unsigned int {
		OK = 0,
		Canceled = 1,
		Aborted = 2,
		Error = 3
	};

}

#endif