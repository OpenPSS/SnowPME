#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <LibShared.hpp>


namespace Sce::Pss::Core {
	using namespace Shared::Debug;

	static std::vector<std::string> messages;

	void ExceptionInfo::AddMessage(const std::string& message) {
		messages.push_back(message);
		Logger::Error(message);
	}
}