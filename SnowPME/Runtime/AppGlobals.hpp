#ifndef SNOW_PME_RUNTIME_APPGLOBAL_H
#define SNOW_PME_RUNTIME_APPGLOBAL_H 1
#include <IO/Sandbox.hpp>
using namespace SnowPME::IO;

#define FILETIME_TICK 10000000LL
#define UNIX_EPOCH 11644473600LL
#define UNIX_TO_FILETIME_MAGIC (UNIX_EPOCH * FILETIME_TICK)

#define FILETIME_TO_UNIX(filetime) (time_t)(filetime == -1 ? filetime : filetime / FILETIME_TICK - UNIX_EPOCH);

namespace SnowPME::Runtime {
	class AppGlobals {
	public:
		static Sandbox* PsmSandbox();
		static void SetPsmSandbox(Sandbox* Sandbox);
	};
}
#endif