#include <LibShared.hpp>
#include <Runtime/ApplicationEvent.hpp>
#include <Runtime/Application.hpp>
#include <memory>
#include <SDL.h>
#include <LibImGui.hpp>

using namespace Shared::Debug;
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
				case SDL_QUIT:
					Application::RunPssTerminate();
					state.Closed = true;
					exit(0);
					break;
				case SDL_WINDOWEVENT:
					if (sdlEvt.window.windowID != SDL_GetWindowID(window)) break;

					switch (sdlEvt.window.event) {
					case SDL_WINDOWEVENT_MAXIMIZED:
						state.Maximized = true;
						break;
					case SDL_WINDOWEVENT_RESIZED:
						state.Maximized = false;
						break;
					case SDL_WINDOWEVENT_MINIMIZED:
						state.Minmized = true;
						state.Restored = false;
						break;
					case SDL_WINDOWEVENT_RESTORED:
						state.Restored = true;
						state.Minmized = false;
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						state.Focused = false;
						break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						state.Focused = true;
					}

					break;
				case SDL_MOUSEBUTTONDOWN:
					state.TouchActive = true;
					SDL_GetMouseState(&state.TouchX, &state.TouchY);
					break;
				case SDL_MOUSEBUTTONUP:
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