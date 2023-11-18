#include <Sce/PlayStation/Core/Error.hpp>
#include <Sce/PlayStation/Core/Environment/Shell.hpp>
#include <Sce/Pss/Core/Environment/ShellNative.hpp>

#include <LibShared.hpp>

namespace Sce::PlayStation::Core::Environment {
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

		
		Sce::Pss::Core::Environment::ShellNative* shell = new Sce::Pss::Core::Environment::ShellNative(data->type, p0, p1, p2, p3);
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
