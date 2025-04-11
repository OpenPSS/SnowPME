#ifndef LIB_PSS_MONO_MONOUTIL_H
#define LIB_PSS_MONO_MONOUTIL_H 1
#include <mono/mono.h>
#include <string>

namespace Sce::Pss::Core::Mono {
	class MonoUtil {
	public:
		static size_t MonoArrayLength(MonoArray* ar);
		static MonoType* MonoArrayElementsType(MonoArray* ar);
		static bool MonoTypeIsValueType(MonoType* type);
		static std::string* MonoStringToStdString(MonoString* mstr, std::string& string);
		static MonoString* StdStringToMonoString(const std::string& str);
		static MonoAssembly* MonoAssemblyOpenFull(MonoDomain* domain, const char* exePath);
	};
}
#endif