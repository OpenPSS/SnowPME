#ifndef LIB_PSS_EXCEPTIONINFO_H
#define LIB_PSS_EXCEPTIONINFO_H 1
#include <vector>
#include <string>

namespace Sce::Pss::Core {
	class ExceptionInfo {
	public:
		static void AddMessage(const std::string& message);
	};
}

#endif