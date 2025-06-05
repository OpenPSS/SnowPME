#ifndef LIB_PSS_INIT_H
#define LIB_PSS_INIT_H 1
#include <string>

#include <mono/mono.h>

namespace Sce::Pss::Core::Mono
{
	class InitializeMono {
	private:
		static MonoDomain* psmDomain;

		static int scePsmExecute(const char* exeFile, int* resCode);
		static int scePsmMonoJitExec2(MonoAssembly* assembly, char** argv, int argc);
		static int exitCallback(int code);

	public:
		static int ScePsmInitalize(const char* assemblyPath, int resourceHeapSize);
		static int ScePsmTerminate();
		static int ScePssMain(const char* gameFolder);
	};
}

#endif