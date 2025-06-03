#include <Runtime/Application.hpp>
#include <Debug/Logger.hpp>

#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <LibCXML.hpp>

#include <Callback/WindowImpl.hpp>

#include <string>
#include <thread>

using namespace Sce::Pss::Core::Mono;
using namespace Shared::Debug;
using namespace Shared;


namespace SnowPME::Runtime {
	std::shared_ptr<Application> Application::runningApplication = nullptr;

	int Application::initCallbacks(std::shared_ptr<Graphics::Window> window) {
		Callback::WindowImpl::Init(window);

		Sce::Pss::Core::Callback::WindowCallbacks::Init(
			Callback::WindowImpl::SwapBuffers,
			Callback::WindowImpl::GetTime,
			Callback::WindowImpl::PollEvents,
			Callback::WindowImpl::WasClosed,
			Callback::WindowImpl::WasMinimized,
			Callback::WindowImpl::YesNoMessageBox);

		return PSM_ERROR_NO_ERROR;
	}
	

	Application::Application(const std::string& gameFolder, std::shared_ptr<Graphics::Window> window) {
		this->appWindow = window;
		this->appMainDirectory = gameFolder;
		Application::initCallbacks(window);
	}

	void Application::RunPssMain() {
		this->appWindow->MakeCurrent();
		InitalizeMono::ScePssMain(this->appMainDirectory.c_str());
	}

	void Application::LoadApplication(const std::string& gameFolder, std::shared_ptr<Graphics::Window> window) {
		if (Application::runningApplication != nullptr) {
			Application::runningApplication = nullptr;
		}
		
		Application::runningApplication = std::make_shared<Application>(gameFolder, window);
		Application::runningApplication->RunPssMain();
	}
}