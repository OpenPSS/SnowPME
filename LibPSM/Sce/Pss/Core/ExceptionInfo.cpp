#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
namespace Sce::Pss::Core {
	static std::vector<std::string> messages;

	void ExceptionInfo::AddMessage(std::string message) {
		messages.push_back(message);
		Logger::Error(message);
	}
}