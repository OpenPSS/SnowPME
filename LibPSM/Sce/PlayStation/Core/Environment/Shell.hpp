#ifndef LIB_PSM_SHELL_H
#define LIB_PSM_SHELL_H 1
#include <iostream>
#include <mono/mono.h>

#include <Sce/PlayStation/Core/Environment/Action.hpp>

namespace Sce::PlayStation::Core::Environment {
	class Shell {
	public:
		static int ExecuteNative(Action *data);
	};
}
#endif
