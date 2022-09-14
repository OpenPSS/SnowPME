#ifndef SNOW_PME_MONO_INIT_H
#define SNOW_PME_MONO_INIT_H 1
#include <mono/mono.h>
#include <string>


namespace SnowPME::Runtime
{
	class Init {
	private:
		static std::string executableFile;
		static void addFunctions();
		static void launchProgram(MonoAssembly* assembly, char* path);
	public:
		static int InitMono(std::string executablePath);
	};
}

#endif