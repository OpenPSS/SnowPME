#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;

namespace Sce::Pss::Core {

	std::string ExceptionInfo::message = "";
	std::string ExceptionInfo::param = "";

	std::string& ExceptionInfo::GetMessage() {
		return message;
	}
	
	std::string& ExceptionInfo::GetParam() {
		return param;
	}

	void ExceptionInfo::SetMessage(const std::string& str) {
		Logger::Debug("ExceptionInfo::SetMessage(\"" + StringUtil::Replace(str, "\n", "") + "\");");

		ExceptionInfo::message = str + "\n";
	}

	void ExceptionInfo::SetMessage(const char* str) {
		Logger::Debug("ExceptionInfo::SetMessage(\"" + StringUtil::Replace(std::string(str), "\n", "") + "\");");

		if (str != nullptr) {
			ExceptionInfo::message = std::string(str, strlen(str)) + "\n";
		}
		else {
			ExceptionInfo::message = std::string();
		}
	}

	void ExceptionInfo::SetParam(const std::string& str) {
		Logger::Debug("ExceptionInfo::SetParam(\"" + StringUtil::Replace(str, "\n", "") + "\");");

		ExceptionInfo::param = str;
	}

	void ExceptionInfo::SetParam(const char* str) {
		Logger::Debug("ExceptionInfo::SetParam(\"" + StringUtil::Replace(std::string(str), "\n", "") + "\");");

		if (str != nullptr) {
			ExceptionInfo::param = std::string(param, strlen(str));
		}
		else {
			ExceptionInfo::param = std::string();
		}
	}

	void ExceptionInfo::AddMessage(const std::string& str) {
		Logger::Debug("ExceptionInfo::AddMessage(\"" + StringUtil::Replace(str, "\n", "") + "\");");

		if (ExceptionInfo::message.empty())
			ExceptionInfo::message += "\n";

		ExceptionInfo::message += str;
	}
}