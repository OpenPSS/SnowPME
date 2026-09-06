#include <LibShared.hpp>
#include <Runtime/ApplicationEvent.hpp>
#include <Runtime/Application.hpp>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

#include <LibImGui.hpp>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Shared::Windowing;
using namespace SnowPME::Graphics;


namespace SnowPME::Runtime {

	std::mutex ApplicationEvent::captureLock;
	Capture ApplicationEvent::state;
	std::atomic<bool> ApplicationEvent::initalized;

	void ApplicationEvent::Init() {
		WindowControl::Init(
			ApplicationEvent::SwapBuffers,
			ApplicationEvent::GetTime,
			ApplicationEvent::FrameStart,
			ApplicationEvent::FrameEnd,
			ApplicationEvent::YesNoMessageBox,
			ApplicationEvent::GetBackend);
		initalized = true;
	}

	std::string ApplicationEvent::GetBackend() {
		return Window::GetMainWindow()->Backend->Name();
	}
	bool ApplicationEvent::YesNoMessageBox(const char* message, const char* caption) {
		return Window::GetMainWindow()->ShowMessageBox(message, caption);
	}

	void ApplicationEvent::SwapBuffers() {
		Window::GetMainWindow()->SwapBuffers();
	}

	uint64_t ApplicationEvent::GetTime() {
		return static_cast<uint64_t>(Window::GetMainWindow()->GetTime());
	}

	void ApplicationEvent::FrameStart() {
		// TODO: Use ImGui while game is running?
	}

	void ApplicationEvent::FrameEnd() {
		// TODO: Use ImGui while game is running?
	}

	void ApplicationEvent::ProcessEvent() {
		if (Application::IsRunning()) {
			SDL_Window* window = Window::GetMainWindow()->GetSdlWindow();
			SDL_Event sdlEvt;

			// sdl event loop

			if (SDL_PollEvent(&sdlEvt)) {

				switch (sdlEvt.type) {
				case SDL_EVENT_QUIT:
					Application::RunPssTerminate();
					state.Closed = true;
					exit(0);
					break;
				case SDL_EVENT_WINDOW_MAXIMIZED:
					state.Maximized = true;
					break;
				case SDL_EVENT_WINDOW_RESIZED:
					state.Maximized = false;
					break;
				case SDL_EVENT_WINDOW_MINIMIZED:
					state.Minmized = true;
					state.Restored = false;
					break;
				case SDL_EVENT_WINDOW_RESTORED:
					state.Restored = true;
					state.Minmized = false;
					break;
				case SDL_EVENT_WINDOW_FOCUS_LOST:
					state.Focused = false;
					break;
				case SDL_EVENT_WINDOW_FOCUS_GAINED:
					state.Focused = true;
					break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					state.TouchActive = true;
					float x, y;
					SDL_GetMouseState(&x, &y);
					state.TouchX = x;
					state.TouchY = y;
					break;
				case SDL_EVENT_MOUSE_BUTTON_UP:
					state.TouchActive = false;
					break;
				}
			}

			// psm event loop

			std::shared_ptr<Event> psmEvt = EventQueue::GetNextRequest();
			if (psmEvt != nullptr) {
				
				switch (psmEvt->TypeID()) {
					case EventType::Capture: // capture current window state
					{
						psmEvt->PutResponse(&state, sizeof(Capture));
						break;
					}
					case EventType::RunFunction: // run arbitary function on main thread ..
					{
						RunFunction* func = reinterpret_cast<RunFunction*>(psmEvt->ArgumentArray());
						uintptr_t res = func->functionPointer(func->arg0, func->arg1, func->arg2, func->arg3);
						psmEvt->PutResponse(&res, sizeof(res));

						break;
					}
					default:
					{
						Logger::Error("EventType is unknown value: " + std::to_string(static_cast<uint32_t>(psmEvt->TypeID())));
						break;
					}
				}

			}

		}
	}

}