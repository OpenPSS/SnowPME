#include <LibShared.hpp>
#include <Runtime/ApplicationEvent.hpp>
#include <Runtime/Application.hpp>
#include <memory>
#include <SDL2/SDL.h>

using namespace Shared::Debug;
using namespace Shared::Windowing;
using namespace SnowPME::Graphics;


namespace SnowPME::Runtime {

	std::mutex ApplicationEvent::captureLock;
	Capture ApplicationEvent::state;

	bool ApplicationEvent::YesNoMessageBox(const char* message, const char* caption) {
		return Window::GetMainWindow()->ShowMessageBox(message, caption);
	}

	void ApplicationEvent::SwapBuffers() {
		Window::GetMainWindow()->SwapBuffers();
	}

	uint64_t ApplicationEvent::GetTime() {
		return static_cast<uint64_t>(Window::GetMainWindow()->GetTime());
	}


	void ApplicationEvent::ProcessEvent() {
		if (!Application::IsRunning()) return;

		if (Application::IsRunning()) {
			SDL_Window* window = Window::GetMainWindow()->GetSdlWindow();
			SDL_Event sdlEvt;

			if (SDL_PollEvent(&sdlEvt)) {
				switch (sdlEvt.type) {
				case SDL_QUIT:
					Application::RunPssTerminate();
					exit(0);
					break;
				case SDL_WINDOWEVENT:
					break;
				}
			}

			std::shared_ptr<Event> psmEvt = EventQueue::GetNextRequest();
			if (psmEvt != nullptr) {
				
				switch (psmEvt->TypeID()) {
				case EventType::Capture:
					psmEvt->ArgsReplace(&state, sizeof(Capture));
					break;
				case EventType::RunFunction:
					Logger::Todo("Implement EventType::RunFunction ...");
					ASSERT(psmEvt->TypeID() != EventType::RunFunction);
					break;
				default:
					Logger::Error("EventType is unknown value: " + std::to_string(static_cast<uint32_t>(psmEvt->TypeID())));
					break;
				}

				// push response.
				EventQueue::PushResponse(psmEvt);

			}

		}
	}

}