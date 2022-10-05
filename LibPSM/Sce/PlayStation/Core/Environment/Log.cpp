#include "Log.hpp"
#include "../Error.hpp"
#include <LibSnowPME.hpp>
using namespace SnowPME::Debug;
using namespace Sce::PlayStation::Core;

namespace Sce::PlayStation::Core::Environment {
	int Log::WriteNative(MonoString* text){
		Logger::Debug(__FUNCTION__);

		if (!text) {
			Logger::Error("\"text\" was a nullptr.");
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		}
		char* str = mono_string_to_utf8(text);
		Logger::Info(std::string(str));
		mono_free(text);
		return PSM_ERROR_NO_ERROR;
	}
	int Log::GetNeedsRedirection(){
		Logger::Debug(__FUNCTION__);

		Logger::Debug("Redirection Needed: false");
		return false;
	}
}
