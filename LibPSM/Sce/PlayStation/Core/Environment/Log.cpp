#include <Sce/PlayStation/Core/Environment/Log.hpp>
#include <Sce/PlayStation/Core/Error.hpp>
#include <LibShared.hpp>

namespace Sce::PlayStation::Core::Environment {
	int Log::WriteNative(MonoString* text){
		Shared::Debug::Logger::Debug(__FUNCTION__);

		if (!text) {
			Shared::Debug::Logger::Error("\"text\" was a nullptr.");
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		}
		char* str = mono_string_to_utf8(text);
		Shared::Debug::Logger::Game(std::string(str));
		mono_free(str);
		return PSM_ERROR_NO_ERROR;
	}
	int Log::GetNeedsRedirection(){
		Shared::Debug::Logger::Debug(__FUNCTION__);
		Shared::Debug::Logger::Debug("Redirection Needed: true");
		return true;
	}
}
