#ifndef LIB_PSS_SHELLNATIVE_H
#define LIB_PSS_SHELLNATIVE_H 1
#include <Sce/PlayStation/Core/Environment/ActionType.hpp>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Environment {
	class ShellNative {
	private:
		ActionType type = ActionType::None;
		std::string paramater0 = "";
		std::string paramater1 = "";
		std::string paramater2 = "";
		std::string paramater3 = "";
		int executeBrowserWindows(std::string url);
		int executeBrowserVita(std::string url);
	public:
		ShellNative(ActionType type, char* p0, char* p1, char* p2, char* p3);
		int Execute();
		int ExecuteBrowser();
	};
}

#endif