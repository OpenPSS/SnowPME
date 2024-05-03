#include <Runtime/Init.hpp>
#include <Debug/Logger.hpp>

#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <LibCXML.hpp>

#include <Callback/WindowImpl.hpp>
#include <Callback/AudioImpl.hpp>

#include <string>

using namespace Shared::Debug;
using namespace Shared;
using namespace LibCXML;


namespace SnowPME::Runtime {

	std::string Init::gameFolder = "";

	int Init::initCallbacks(Graphics::Window* oglWindow) {
		Callback::WindowImpl::Init(oglWindow);

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

	void Init::LoadApplication(std::string gameFolder, Graphics::Window* window) {

		// setup window callbacks
		Init::initCallbacks(window);

		// set game folder ..
		Init::gameFolder = gameFolder;
	}
	

	void Init::StartApplication() {
		// load mono and start program !
		Sce::Pss::Core::Mono::Init::ScePsmMonoInit(gameFolder.c_str());
	}
}