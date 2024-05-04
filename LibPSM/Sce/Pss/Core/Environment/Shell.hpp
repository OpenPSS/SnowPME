#ifndef LIB_PSS_SHELL_H
#define LIB_PSS_SHELL_H 1
#include <iostream>
#include <mono/mono.h>

#include <Sce/Pss/Core/Environment/Action.hpp>

namespace Sce::Pss::Core::Environment {
	class Shell {
	private:
		ActionType type = ActionType::None;
		std::string paramater0 = "";
		std::string paramater1 = "";
		std::string paramater2 = "";
		std::string paramater3 = "";
		int executeBrowserWindows(const std::string& url);
		int executeBrowserVita(const std::string& url);
	public:
		static int ExecuteNative(Action* data);
		Shell(ActionType type, char* p0, char* p1, char* p2, char* p3);
		int Execute();
		int ExecuteBrowser();
	};
}
#endif
