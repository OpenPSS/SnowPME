#include <Util/AppGlobals.hpp>
namespace SnowPME::Util {
	static Sandbox* psmSandbox;
	static AppInfo* psmAppInfo;
	static uint64_t psmMainThreadId;
	static Window* psmMainWindow;
	static uint32_t psmLastError;
	

	uint32_t AppGlobals::PsmLastError() {
		return psmLastError;
	}
	void AppGlobals::SetPsmLastError(uint32_t err) {
		psmLastError = err;
	}

	Window* AppGlobals::PsmMainWindow() {
		return psmMainWindow;
	}

	void AppGlobals::SetPsmMainWindow(Window* mainWindow) {
		psmMainWindow = mainWindow;
	}

	uint64_t AppGlobals::PsmMainThreadId() {
		return psmMainThreadId;
	}

	void AppGlobals::SetPsmMainThreadId(uint64_t threadId) {
		psmMainThreadId = threadId;
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