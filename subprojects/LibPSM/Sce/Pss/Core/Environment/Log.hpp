#ifndef LIB_PSS_LOG_H
#define LIB_PSS_LOG_H 1
#define MONO_ZERO_LEN_ARRAY 1
#include <mono/mono.h>

#include <cstdint>
#include <string>
#include <iostream>


namespace Sce::Pss::Core::Environment {
	class Log {
	private:
	public:
		static int WriteNative(MonoString* text);
		static int GetNeedsRedirection();
	};
}
#endif
