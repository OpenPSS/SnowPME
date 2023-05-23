#include <Sce/Pss/Core/Application.hpp>

using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Metadata;

namespace Sce::Pss::Core {
	static Sandbox* psmSandbox = nullptr;
	static AppInfo* psmAppInfo = nullptr;


	AppInfo* Application::PsmAppInfo() {
		return psmAppInfo;
	}
	void Application::SetPsmAppInfo(AppInfo* appInfo) {
		psmAppInfo = appInfo;
	}

	Sandbox* Application::PsmSandbox() {
		return psmSandbox;
	}
	void Application::SetPsmSandbox(Sandbox* sandbox) {
		psmSandbox = sandbox;
	}

}