#include <Runtime/Application.hpp>
#include <Runtime/ApplicationEvent.hpp>
#include <Debug/Logger.hpp>

#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <LibCXML.hpp>

#include <string>
#include <thread>

using namespace Shared::Debug;
using namespace Shared::Windowing;
using namespace Shared;

using namespace SnowPME::Graphics;
using namespace Sce::Pss::Core::Mono;


namespace SnowPME::Runtime {
	std::string Application::appMainDirectory = "";
	std::thread Application::appThread;
	std::atomic<bool> Application::isRunning = false;

	int Application::RunPssMain() {
		return InitializeMono::ScePssMain(appMainDirectory.c_str());
	}

	void Application::RunPssTerminate() {
		InitializeMono::ScePsmTerminate();
		isRunning = false;
	}

	bool Application::IsRunning() {
		return isRunning;
	}

	int Application::LoadApplication(const std::string& gameFolder) {
		appMainDirectory = gameFolder;
		isRunning = true;

		return Application::RunPssMain();
	}
}