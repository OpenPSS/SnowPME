#ifndef SNOW_PME_RUNTIME_INIT_H
#define SNOW_PME_RUNTIME_INIT_H 1
#include <string>
#include <Graphics/Window.hpp>
#include <mono/mono.h>

namespace SnowPME::Runtime
{
	class Init {
	private:
		static std::string appExe;
		static MonoDomain* psmDomain;
		static MonoAssembly* psmCoreLib;
		static MonoAssembly* msCoreLib;
		static MonoAssembly* systemLib;

		static void addFunctions();
		static void launchExe(std::string runExe);
		static int initMono(std::string executablePath);
		static int initCallbacks(Graphics::Window* oglWindow);

	public:
		static void LoadApplication(std::string gameFolder);
		static void StartApplication();
	};
}

#endif