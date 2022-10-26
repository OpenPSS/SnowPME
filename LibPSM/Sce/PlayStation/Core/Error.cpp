#include <Sce/PlayStation/Core/Error.hpp>
#include <mono/mono.h>
namespace Sce::PlayStation::Core {
	int Error::GetExceptionInfoNative(MonoString* message, MonoString* param) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
