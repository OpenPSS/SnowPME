#include <Sce/Pss/Core/Error.hpp>
#include <mono/mono.h>
namespace Sce::Pss::Core {
	int Error::GetExceptionInfoNative(MonoString* message, MonoString* param) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
