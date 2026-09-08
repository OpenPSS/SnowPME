#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <LibShared.hpp>

#include <mono/mono.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core {
	int Error::GetExceptionInfoNative(MonoString* message, MonoString* param) {
		LOG_FUNCTION();
		
		std::string exceptionMessage = ExceptionInfo::GetMessage();
		std::string exceptionParam = ExceptionInfo::GetParam();

		MonoString* monoStrMessage = nullptr;
		MonoString* monoStrParam = nullptr;

		// add exception message;
		if (!exceptionMessage.empty()) {
			MonoDomain* domain = mono_domain_get();
			monoStrMessage = mono_string_new(domain, exceptionMessage.c_str());
		}
		mono_gc_wbarrier_generic_store(message, (MonoObject*)monoStrMessage);

		// add exeception param;
		if (!exceptionParam.empty()) {
			MonoDomain* domain = mono_domain_get();
			monoStrParam = mono_string_new(domain, exceptionMessage.c_str());
		}
		mono_gc_wbarrier_generic_store(param, (MonoObject*)monoStrParam);

		ExceptionInfo::SetMessage("");
		ExceptionInfo::SetParam("");
		return PSM_ERROR_NO_ERROR;
	}
}
