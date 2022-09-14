#ifndef LIB_PSM_LOG_H
#define LIB_PSM_LOG_H 1
#include <mono/mono.h>

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {
	class Log {
	public:
		static int WriteNative(MonoString* text);
		static int GetNeedsRedirection();
	};
}
#endif
