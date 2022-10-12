#ifndef SNOW_PME_MONO_UTIL_H
#define SNOW_PME_MONO_UTIL_H 1
#include <mono/mono.h>
namespace SnowPME::Util {
	class MonoUtil {
	public:
		static size_t MonoArrayLength(MonoArray* ar);
		static MonoType* MonoArrayElementsType(MonoArray* ar);
		static bool MonoTypeIsValueType(MonoType* type);
	};
}
#endif