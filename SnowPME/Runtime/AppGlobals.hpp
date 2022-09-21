#ifndef SNOW_PME_RUNTIME_APPGLOBAL_H
#define SNOW_PME_RUNTIME_APPGLOBAL_H 1
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