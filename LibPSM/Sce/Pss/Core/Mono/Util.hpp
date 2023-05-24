#ifndef LIB_PSS_MONO_UTIL_H
#define LIB_PSS_MONO_UTIL_H 1
#include <mono/mono.h>
namespace Sce::Pss::Core::Mono {
	class Util {
	public:
		static size_t MonoArrayLength(MonoArray* ar);
		static MonoType* MonoArrayElementsType(MonoArray* ar);
		static bool MonoTypeIsValueType(MonoType* type);
	};
}
#endif