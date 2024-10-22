#ifndef LIB_PSS_INIT_H
#define LIB_PSS_INIT_H 1
#include <string>
#include <mono/mono.h>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>

namespace Sce::Pss::Core::Mono
{
	class InitalizeMono {
	private:
		static MonoDomain* psmDomain;

		static int scePsmExecute(const char* exeFile, int* resCode);
		static int scePsmMonoJitExec2(MonoAssembly* assembly, char** argv, int argc);

	public:
		static int ScePsmInitalize(const char* assemblyPath, Sce::Pss::Core::Metadata::AppInfo* settings);
		static int ScePsmTerminate();
		static int ScePssMain(const char* gameFolder);
	};
}

#endif