#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <LibShared.hpp>
#include <cstring>

using namespace Shared::Debug;
using namespace Shared::String;

namespace Sce::Pss::Core {

	std::string ExceptionInfo::message = "";
	std::string ExceptionInfo::param = "";

	std::string& ExceptionInfo::GetMessage() {
		LOG_FUNCTION();

		return message;
	}
	
	std::string& ExceptionInfo::GetParam() {
		LOG_FUNCTION();

		return param;
	}

	void ExceptionInfo::SetMessage(const std::string& str) {
		LOG_FUNCTION();

		ExceptionInfo::message = str + "\n";
	}

	void ExceptionInfo::SetMessage(const char* str) {
		LOG_FUNCTION();

		if (str != nullptr) {
			ExceptionInfo::message = std::string(str, strlen(str)) + "\n";
		}
		else {
			ExceptionInfo::message = std::string();
		}
	}

	void ExceptionInfo::SetParam(const std::string& str) {
		LOG_FUNCTION();

		ExceptionInfo::param = str;
	}

	void ExceptionInfo::SetParam(const char* str) {
		LOG_FUNCTION();

		if (str != nullptr) {
			ExceptionInfo::param = std::string(param, strlen(str));
		}
		else {
			ExceptionInfo::param = std::string();
		}
	}

	void ExceptionInfo::AddMessage(const std::string& str) {
		LOG_FUNCTION();

		if (ExceptionInfo::message.empty())
			ExceptionInfo::message += "\n";

		ExceptionInfo::message += str;
	}
}