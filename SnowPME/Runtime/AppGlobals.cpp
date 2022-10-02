#include <Runtime/AppGlobals.hpp>
namespace SnowPME::Runtime {
	static Sandbox* psmSandbox;
	static AppInfo* psmAppInfo;

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