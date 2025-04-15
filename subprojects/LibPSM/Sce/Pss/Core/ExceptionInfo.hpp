#ifndef LIB_PSS_EXCEPTIONINFO_H
#define LIB_PSS_EXCEPTIONINFO_H 1
#include <string>

namespace Sce::Pss::Core {
	class ExceptionInfo {
	private:
		static std::string message;
		static std::string param;

	public:
		static std::string& GetMessage();
		static std::string& GetParam();

		static void SetMessage(const std::string& str);
		static void SetMessage(const char* str);

		static void SetParam(const std::string& str);
		static void SetParam(const char* str);

		static void AddMessage(const std::string& str);
	};
}

#endif