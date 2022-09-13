#ifndef SNOW_PME_MONO_INIT_H
#define SNOW_PME_MONO_INIT_H 1
#include <SnowPME/Mono.h>
#include <string>

using namespace std;
namespace SnowPME::Mono
{
	class Init {
	private:
		static string executableFile;
		static void addFunctions();
		static void launchProgram(MonoAssembly* assembly, char* path);
	public:
		static int InitMono(string executablePath);
	};
}

#endif