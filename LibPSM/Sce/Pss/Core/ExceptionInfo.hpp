#ifndef LIB_PSM_EXCEPTIONINFO_H
#define LIB_PSM_EXCEPTIONINFO_H 1
#include <vector>
#include <string>

namespace Sce::Pss::Core {
	class ExceptionInfo {
	public:
		static void AddMessage(std::string message);
	};
}

#endif