#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <LibShared.hpp>
#include <cstring>

using namespace Shared::Debug;
using namespace Shared::String;

namespace Sce::Pss::Core {

	std::string ExceptionInfo::message = "";
	std::string ExceptionInfo::param = "";

	std::string ExceptionInfo::GetMessage() {
		LOG_FUNCTION();

		Logger::Debug("Exception read .. " + message);

		return message;
	}
	
	std::string ExceptionInfo::GetParam() {
		LOG_FUNCTION();

		return param;
	}

	void ExceptionInfo::SetMessage(const std::string& str) {
		LOG_FUNCTION();

		ExceptionInfo::message = str;
	}

	void ExceptionInfo::SetMessage(const char* str) {
		LOG_FUNCTION();

		if (str != nullptr) {
			ExceptionInfo::message = std::string(str, strlen(str));
		}
		else {
			ExceptionInfo::message = "";
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
			ExceptionInfo::param = "";
		}
	}

	void ExceptionInfo::AddMessage(const std::string& str) {
		LOG_FUNCTION();

		Logger::Debug("Exception write .. " + str);
		Logger::Error(str);

		if (ExceptionInfo::message.empty())
			ExceptionInfo::message += "\n";

		ExceptionInfo::message += str;
	}
}