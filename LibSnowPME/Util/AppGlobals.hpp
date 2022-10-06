#ifndef SNOW_PME_RUNTIME_APPGLOBAL_H
#define SNOW_PME_RUNTIME_APPGLOBAL_H 1
#include <IO/Sandbox.hpp>
#include <Graphics/Window.hpp>
#include <Metadata/AppInfo.hpp>

using namespace SnowPME::IO;
using namespace SnowPME::Metadata;
using namespace SnowPME::Graphics;

#define FILETIME_TICK 10000000LL
#define UNIX_EPOCH 11644473600LL

#define FILETIME_TO_UNIX(filetime) (time_t)(filetime == -1 ? filetime : filetime / FILETIME_TICK - UNIX_EPOCH);
#define UNIX_TO_FILETIME(unixtime) ((unixtime+UNIX_EPOCH) * FILETIME_TICK);

#ifdef _MSC_VER
typedef wchar_t wchar;
#endif

namespace SnowPME::Util {
	class AppGlobals {
	public:
		static uint32_t PsmLastError();
		static void SetPsmLastError(uint32_t err);

		static Window* PsmMainWindow();
		static void SetPsmMainWindow(Window* mainWindow);

		static uint64_t PsmMainThreadId();
		static void SetPsmMainThreadId(uint64_t threadId);

		static AppInfo* PsmAppInfo();
		static void SetPsmAppInfo(AppInfo* Sandbox);

		static Sandbox* PsmSandbox();
		static void SetPsmSandbox(Sandbox* Sandbox);
	};
}
#endif