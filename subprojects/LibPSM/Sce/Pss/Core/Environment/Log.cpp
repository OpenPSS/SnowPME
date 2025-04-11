#include <Sce/Pss/Core/Environment/Log.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <LibShared.hpp>


namespace Sce::Pss::Core::Environment {
	using namespace Sce::Pss::Core;
	using namespace Shared::Debug;

	int Log::WriteNative(MonoString* text){
		Shared::Debug::Logger::Debug(__FUNCTION__);

		if (!text) {
			Logger::Error("\"text\" was a nullptr.");
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		}

		std::string msg;
		Mono::MonoUtil::MonoStringToStdString(text, msg);
		Logger::Game(msg);

		return PSM_ERROR_NO_ERROR;
	}
	int Log::GetNeedsRedirection(){
		Logger::Debug(__FUNCTION__);

		// This was set based on what was being implemented,
		switch (Shared::Config::TargetImplementation) {
		case Shared::RuntimeImplementation::Windows:
			Logger::Debug("Redirection Needed: false");
			return false;
		case Shared::RuntimeImplementation::PSVita:
		case Shared::RuntimeImplementation::Android:
			Logger::Debug("Redirection Needed: true");
			return true;
		}

		return true;
	}
}
