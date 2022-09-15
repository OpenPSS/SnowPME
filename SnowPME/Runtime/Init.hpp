#ifndef SNOW_PME_MONO_INIT_H
#define SNOW_PME_MONO_INIT_H 1
#include <mono/mono.h>
#include <string>

#define PSM_MAIN_EXECUTABLE "app.exe"

namespace SnowPME::Runtime
{
	class Init {
	private:
		static void addFunctions();
		static void launchExe(std::string runExe);
		static int initMono(std::string executablePath);
	public:
		static void LoadApplication(std::string gameFolder);
		static void StartApplication();
	};
}

#endif