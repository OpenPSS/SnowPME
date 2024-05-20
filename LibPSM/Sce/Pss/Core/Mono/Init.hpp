#ifndef LIB_PSS_INIT_H
#define LIB_PSS_INIT_H 1
#include <string>
#include <mono/mono.h>
namespace Sce::Pss::Core::Mono
{
	class Init {
	private:
		static std::string appExe;
		static MonoDomain* psmDomain;
		static MonoAssembly* psmCoreLib;
		static MonoAssembly* msCoreLib;
		static MonoAssembly* systemLib;

		static int initMono(std::string gameFolder);
		static int initMonoAssembly(std::string exeFile);

		static void launchExe();
		static void addFunctions();

	public:
		static void ScePsmMonoInit(const char* gameFolder);
	};
}

#endif