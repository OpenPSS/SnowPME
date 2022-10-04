#include <Util/AppGlobals.hpp>
namespace SnowPME::Util {
	static Sandbox* psmSandbox;
	static AppInfo* psmAppInfo;
	static uint64_t psmMainThreadId;

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