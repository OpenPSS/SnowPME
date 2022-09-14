#include "Log.hpp"
#include "../Error.hpp"
using namespace Sce::PlayStation::Core;

namespace Sce::PlayStation::Core::Environment {
	int Log::WriteNative(MonoString* text){
		if (!text) {
#ifdef _DEBUG
			std::cout << "Log::WriteNative() ERROR: Text* = NULL" << std::endl;
#endif
			return SCE_PSM_ERROR_COMMON_ARGUMENT_NULL;
		}
		char* str = mono_string_to_utf8(text);
		std::cout << "[LOG] " << std::string(str);
		mono_free(text);
		return 0;
	}
	int Log::GetNeedsRedirection(){
#ifdef _DEBUG
		std::cout << "Log::GetNeedsRedirection() = 0" << std::endl;
#endif
		return 0;
	}
}
