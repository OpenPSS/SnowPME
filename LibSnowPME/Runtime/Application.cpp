#include <Runtime/Application.hpp>
#include <Debug/Logger.hpp>

#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <LibCXML.hpp>

#include <Callback/WindowImpl.hpp>
#include <Callback/AudioImpl.hpp>

#include <string>
#include <thread>

using namespace Sce::Pss::Core::Mono;
using namespace Shared::Debug;
using namespace Shared;
using namespace LibCXML;


namespace SnowPME::Runtime {
	Application* Application::runningApplication = nullptr;
	std::thread* Application::psmGameThread = nullptr;

	int Application::initCallbacks(Graphics::Window* window) {
		Callback::WindowImpl::Init(window);

		Sce::Pss::Core::Callback::WindowCallbacks::Init(
			Callback::WindowImpl::SwapBuffers,
			Callback::WindowImpl::GetTime,
			Callback::WindowImpl::PollEvents,
			Callback::WindowImpl::WasClosed,
			Callback::WindowImpl::WasMinimized,
			Callback::WindowImpl::YesNoMessageBox);

		Callback::AudioImpl::Init();
		Sce::Pss::Core::Callback::AudioCallbacks::Init(
			Callback::AudioImpl::OpenMP3,
			Callback::AudioImpl::CloseMP3,
			Callback::AudioImpl::PlayMP3,
			Callback::AudioImpl::PauseMP3,
			Callback::AudioImpl::ResumeMP3,
			Callback::AudioImpl::StopMP3,
			Callback::AudioImpl::IsMP3Paused,
			Callback::AudioImpl::IsMP3Playing,
			Callback::AudioImpl::IsMP3Stopped,
			Callback::AudioImpl::SetLoop);

		return PSM_ERROR_NO_ERROR;
	}


	Application::Application(const std::string& gameFolder, Graphics::Window* window) {
		this->appWindow = window;
		this->appMainDirectory = gameFolder;
	}

	void Application::RunPssMain() {
		this->appWindow->MakeCurrent();
		InitalizeMono::ScePssMain(this->appMainDirectory.c_str());
	}

	void Application::LoadApplication(const std::string& gameFolder, Graphics::Window* window) {
		// setup window callbacks
		Application::initCallbacks(window);

		if (Application::runningApplication != nullptr) {
			delete Application::runningApplication;
			Application::runningApplication = nullptr;
		}

		if (Application::psmGameThread != nullptr) {
			Application::psmGameThread->join();
			Application::psmGameThread = nullptr;
		}
		
		Application::runningApplication = new Application(gameFolder, window);
		Application::runningApplication->RunPssMain();
	}
}