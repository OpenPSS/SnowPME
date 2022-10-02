#include "Log.hpp"
#include "../Error.hpp"
using namespace Sce::PlayStation::Core;

namespace Sce::PlayStation::Core::Environment {
	int Log::WriteNative(MonoString* text){
		if (!text) {
			std::cout << "[ERROR] Log::WriteNative() - Text* = NULL" << std::endl;
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		}
		char* str = mono_string_to_utf8(text);
		std::cout << "[INFO] " << std::string(str);
		mono_free(text);
		return 0;
	}
	int Log::GetNeedsRedirection(){
#ifdef _DEBUG
		std::cout << "[DEBUG] Log::GetNeedsRedirection() = 0" << std::endl;
#endif
		return 0;
	}
}
