#ifndef SNOW_PME_RUNTIME_APPGLOBAL_H
#define SNOW_PME_RUNTIME_APPGLOBAL_H 1
#ifdef _DEBUG
#define LOG(x) std::cout << "[LOG] " << x << std::endl
#else
#define LOG(x) /*x*/
#endif
#include <IO/Sandbox.hpp>
using namespace SnowPME::IO;

namespace SnowPME::Runtime {
	class AppGlobals {
	public:
		static Sandbox* PsmSandbox();
		static void SetPsmSandbox(Sandbox* Sandbox);
	};
}
#endif