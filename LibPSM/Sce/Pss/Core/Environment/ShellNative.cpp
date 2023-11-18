#include <Sce/Pss/Core/Environment/ShellNative.hpp>
#include <Sce/Pss/Core/Graphics/WindowSystemCallbacks.hpp>
#include <Sce/Pss/Core/PlatformSpecific.hpp>
#include <LibShared.hpp>
namespace Sce::Pss::Core::Environment {
	ShellNative::ShellNative(ActionType type, char* p0, char* p1, char* p2, char* p3) {

		this->type = type;
	
		if(p0 != nullptr)
			this->paramater0 = std::string(p0);

		if (p1 != nullptr)
			this->paramater1 = std::string(p1);

		if (p2 != nullptr)
			this->paramater2 = std::string(p2);

		if (p3 != nullptr)
			this->paramater3 = std::string(p3);
	}

	int ShellNative::Execute() {
		switch (this->type) {
		case ActionType::Browser:
			return this->ExecuteBrowser();
		case ActionType::None:
		default:
			return PSM_ERROR_COMMON_ARGUMENT;
		}
	}
	int ShellNative::executeBrowserWindows(std::string url) {
		if (Graphics::WindowSystemCallbacks::YesNoDialog("Do you want to open \"" + url + "\"?", "Website Open Request"))
			return PlatformSpecific::OpenWebsite(url);

		return PSM_ERROR_NO_ERROR;

	}

	int ShellNative::executeBrowserVita(std::string url) {
		return PlatformSpecific::OpenWebsite(url);
	}

	int ShellNative::ExecuteBrowser() {
		std::string url = this->paramater0.substr(0, 2048);
		switch (Shared::Config::TargetImplementation) {
			case Shared::RuntimeImplementation::Windows:
				return this->executeBrowserWindows(url);
			case Shared::RuntimeImplementation::PSVita:
			case Shared::RuntimeImplementation::Android:
				return this->executeBrowserVita(url);
		}

	}

}