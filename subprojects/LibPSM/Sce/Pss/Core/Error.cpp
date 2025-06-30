#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <LibShared.hpp>

#include <mono/mono.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core {
	int Error::GetExceptionInfoNative(MonoString* message, MonoString* param) {
		LOG_FUNCTION();
		
		const char* exceptionMessage = ExceptionInfo::GetMessage().c_str();
		const char* exceptionParam = ExceptionInfo::GetParam().c_str();

		MonoString* monoStrMessage = nullptr;
		MonoString* monoStrParam = nullptr;

		// add exception message;
		if (exceptionMessage[0] != 0x00) {
			MonoDomain* domain = mono_domain_get();
			monoStrMessage = mono_string_new(domain, exceptionMessage);
		}
		mono_gc_wbarrier_generic_store(message, (MonoObject*)monoStrMessage);

		// add exeception param;
		if (exceptionParam[0] != 0x00) {
			MonoDomain* domain = mono_domain_get();
			monoStrParam = mono_string_new(domain, exceptionMessage);
		}
		mono_gc_wbarrier_generic_store(param, (MonoObject*)monoStrParam);

		ExceptionInfo::SetMessage("");
		ExceptionInfo::SetParam("");
		return PSM_ERROR_NO_ERROR;
	}
}
