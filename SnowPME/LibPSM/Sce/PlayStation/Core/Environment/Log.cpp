#include "Log.hpp"
#include "../Error.hpp"
using namespace Sce::PlayStation::Core;

namespace Sce::PlayStation::Core::Environment {
	int Log::WriteNative(MonoString* text){
		if (!text) {
#ifdef _DEBUG
			cout << "Log::WriteNative() ERROR: Text* = NULL" << endl;
#endif
			return SCE_PSM_ERROR_COMMON_ARGUMENT_NULL;
		}
		char* str = mono_string_to_utf8(text);
		cout << "[LOG] " << string(str);
		mono_free(text);
		return 0;
	}
	int Log::GetNeedsRedirection(){
#ifdef _DEBUG
		cout << "Log::GetNeedsRedirection() = 0" << endl;
#endif
		return 0;
	}
}
