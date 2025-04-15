#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;

namespace Sce::Pss::Core {

	std::string ExceptionInfo::message = "";
	std::string ExceptionInfo::param = "";

	std::string& ExceptionInfo::GetMessage() {
		Logger::Debug(__FUNCTION__);

		return message;
	}
	
	std::string& ExceptionInfo::GetParam() {
		Logger::Debug(__FUNCTION__);

		return param;
	}

	void ExceptionInfo::SetMessage(const std::string& str) {
		Logger::Debug(__FUNCTION__);
		Logger::Debug("ExceptionInfo::SetMessage(\"" + str + "\");");

		ExceptionInfo::message = str + "\n";
	}

	void ExceptionInfo::SetMessage(const char* str) {
		Logger::Debug(__FUNCTION__);
		Logger::Debug("ExceptionInfo::SetMessage(\"" + std::string(str) + "\");");

		if (str != nullptr) {
			ExceptionInfo::message = std::string(str, strlen(str)) + "\n";
		}
		else {
			ExceptionInfo::message = std::string();
		}
	}

	void ExceptionInfo::SetParam(const std::string& str) {
		Logger::Debug(__FUNCTION__);
		Logger::Debug("ExceptionInfo::SetParam(\"" + str + "\");");

		ExceptionInfo::param = str;
	}

	void ExceptionInfo::SetParam(const char* str) {
		Logger::Debug(__FUNCTION__);
		Logger::Debug("ExceptionInfo::SetParam(\"" + std::string(str) + "\");");

		if (str != nullptr) {
			ExceptionInfo::param = std::string(param, strlen(str));
		}
		else {
			ExceptionInfo::param = std::string();
		}
	}

	void ExceptionInfo::AddMessage(const std::string& str) {
		Logger::Debug(__FUNCTION__);
		Logger::Debug("ExceptionInfo::AddMessage(\"" + str + "\");");

		if (ExceptionInfo::message.empty())
			ExceptionInfo::message += "\n";

		ExceptionInfo::message += (str + "\n");
	}
}