#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Environment/Shell.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>
#include <Sce/Pss/Core/Callback/WindowCallbacks.hpp>
#include <LibShared.hpp>
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
	int Shell::executeBrowserWindows(std::string url) {
		if (Callback::WindowCallbacks::YesNoDialog("Do you want to open \"" + url + "\"?", "Website Open Request"))
			return PlatformSpecific::OpenWebsite(url);

		return PSM_ERROR_NO_ERROR;

	}

	int Shell::executeBrowserVita(std::string url) {
		return PlatformSpecific::OpenWebsite(url);
	}

	int Shell::ExecuteBrowser() {
		std::string url = this->paramater0.substr(0, 2048);
		switch (Shared::Config::TargetImplementation) {
		case Shared::RuntimeImplementation::Windows:
			return this->executeBrowserWindows(url);
		case Shared::RuntimeImplementation::PSVita:
		case Shared::RuntimeImplementation::Android:
			return this->executeBrowserVita(url);
		}

	}
	int Shell::ExecuteNative(Action* data){
		Shared::Debug::Logger::Debug(__FUNCTION__);
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

		
		Shell* shell = new Shell(data->type, p0, p1, p2, p3);
		int ret = shell->Execute();
		delete shell;


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
