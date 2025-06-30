#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Environment/Shell.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>
#include <LibShared.hpp>

using namespace Shared;
using namespace Shared::Windowing;
using namespace Shared::Debug;

using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Environment {

	Shell::Shell(ActionType type, char* p0, char* p1, char* p2, char* p3) {

		this->type = type;

		if (p0 != nullptr)
			this->paramater0 = std::string(p0);

		if (p1 != nullptr)
			this->paramater1 = std::string(p1);

		if (p2 != nullptr)
			this->paramater2 = std::string(p2);

		if (p3 != nullptr)
			this->paramater3 = std::string(p3);
	}

	int Shell::Execute() {
		switch (this->type) {
		case ActionType::Browser:
			return this->ExecuteBrowser();
		case ActionType::None:
		default:
			return PSM_ERROR_COMMON_ARGUMENT;
		}
	}
	int Shell::executeBrowserWindows(const std::string& url) {
		if (WindowControl::YesNoDialog("Do you want to open \"" + url + "\"?", "Website Open Request"))
			return PlatformSpecific::OpenWebsite(url);

		return PSM_ERROR_NO_ERROR;

	}

	int Shell::executeBrowserVita(const std::string& url) {
		return PlatformSpecific::OpenWebsite(url);
	}

	int Shell::ExecuteBrowser() {
		std::string url = this->paramater0.substr(0, 2048);
		switch (Config::TargetImplementation) {
		case RuntimeImplementation::Windows:
			return this->executeBrowserWindows(url);
		case RuntimeImplementation::PSVita:
		case RuntimeImplementation::Android:
			return this->executeBrowserVita(url);
		default:
			UNIMPLEMENTED_MSG("ExecuteBrowser targeting RuntimeImplementation: "+std::to_string(static_cast<uint32_t>(Config::TargetImplementation)));
		}

	}
	int Shell::ExecuteNative(Action* data){
		LOG_FUNCTION();
		if (data == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		char* p0 = nullptr;
		char* p1 = nullptr;
		char* p2 = nullptr;
		char* p3 = nullptr;

		// Get paramaters
		if (data->parameter0 != nullptr)
			p0 = mono_string_to_utf8(data->parameter0);

		if (data->parameter1 != nullptr)
			p1 = mono_string_to_utf8(data->parameter1);

		if (data->parameter2 != nullptr)
			p2 = mono_string_to_utf8(data->parameter2);

		if (data->parameter3 != nullptr)
			p3 = mono_string_to_utf8(data->parameter3);

		
		std::unique_ptr<Shell> shell = std::make_unique<Shell>(data->type, p0, p1, p2, p3);
		int ret = shell->Execute();

		// Free paramaters
		if(p0 != nullptr)
			mono_free(p0);
		
		if(p1 != nullptr)
			mono_free(p1);
		
		if(p2 != nullptr)
			mono_free(p2);
	
		if(p3 != nullptr)
			mono_free(p3);

		return ret;
	}
}
