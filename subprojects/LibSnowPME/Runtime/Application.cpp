#include <Runtime/Application.hpp>
#include <Debug/Logger.hpp>

#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <LibCXML.hpp>

#include <Callback/WindowImpl.hpp>

#include <string>
#include <thread>

using namespace Sce::Pss::Core::Callback;
using namespace Sce::Pss::Core::Mono;
using namespace Shared::Debug;
using namespace Shared;


namespace SnowPME::Runtime {
	std::shared_ptr<Application> Application::runningApplication = nullptr;

	int Application::initCallbacks(std::shared_ptr<Graphics::Window> window) {

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

	int Application::RunPssMain() {
		return InitializeMono::ScePssMain(this->appMainDirectory.c_str());
	}

	void Application::RunPssTerminate() {
		InitializeMono::ScePsmTerminate();
		this->runningApplication = nullptr;
	}

	bool Application::IsRunning() {
		if (Application::runningApplication != nullptr) return true;
		else return false;
	}

	void Application::CheckEvent() {
		if (!Application::IsRunning()) return;

		std::shared_ptr app = Application::runningApplication;
		if (app != nullptr) {
			SDL_Window* window = app->appWindow->GetSdlWindow();
			SDL_Event evt;

			if (SDL_PollEvent(&evt)) {
				switch (evt.type) {
					case SDL_QUIT:
						app->RunPssTerminate();
						exit(0);
						break;
					case SDL_WINDOWEVENT:
						Logger::Debug("evt // SDL_WINDOWEVENT");
						break;
					case SDL_KEYDOWN:
						Logger::Debug("evt // SDL_KEYDOWN");
						break;
					case SDL_KEYUP:
						Logger::Debug("evt // SDL_KEYUP");
						break;
					case SDL_MOUSEMOTION:
						Logger::Debug("evt // SDL_MOUSEMOTION");
						break;
					default:
						Logger::Debug("evt // " + std::to_string(evt.type));
						break;
				}
			}
		}
	}

	int Application::LoadApplication(const std::string& gameFolder, std::shared_ptr<Graphics::Window> window) {
		if (Application::runningApplication != nullptr) {
			Application::runningApplication = nullptr;
		}
		
		Application::runningApplication = std::make_shared<Application>(gameFolder, window);
		return Application::runningApplication->RunPssMain();
	}
}