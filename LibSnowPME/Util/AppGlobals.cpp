#include <Util/AppGlobals.hpp>
#include <LibPSM.hpp>
using namespace Sce::Pss::Core::Io;

namespace SnowPME::Util {
	static Sandbox* psmSandbox;
	static AppInfo* psmAppInfo;
	static Window* psmMainWindow;

	Window* AppGlobals::PsmMainWindow() {
		return psmMainWindow;
	}

	void AppGlobals::SetPsmMainWindow(Window* mainWindow) {
		psmMainWindow = mainWindow;
	}

	AppInfo* AppGlobals::PsmAppInfo() {
		return psmAppInfo;
	}
	void AppGlobals::SetPsmAppInfo(AppInfo* appInfo) {
		psmAppInfo = appInfo;
	}

	Sandbox* AppGlobals::PsmSandbox() {
		return psmSandbox;
	}
	void AppGlobals::SetPsmSandbox(Sandbox* sandbox) {
		psmSandbox = sandbox;
	}
}