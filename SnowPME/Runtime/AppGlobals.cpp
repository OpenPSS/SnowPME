#include <Runtime/AppGlobals.hpp>
namespace SnowPME::Runtime {
	static Sandbox* psmSandbox;

	Sandbox* AppGlobals::PsmSandbox() {
		return psmSandbox;
	}
	void AppGlobals::SetPsmSandbox(Sandbox* Sandbox) {
		psmSandbox = Sandbox;
	}
}