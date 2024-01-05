#include <Callback/WindowImpl.hpp>
using namespace SnowPME::Graphics;

namespace SnowPME::Callback {

	Window* WindowImpl::mainWindow = nullptr;

	void WindowImpl::Init(Window* window) {
		WindowImpl::mainWindow = window;
		WindowImpl::isInitalized = true;
	}

	void WindowImpl::PollEvents() {

		WindowImpl::ErrorOnNotInit();
		WindowImpl::mainWindow->PollEvents();
	}

	bool WindowImpl::WasClosed() {
		WindowImpl::ErrorOnNotInit();
		return WindowImpl::mainWindow->ShouldClose();
	}

	bool WindowImpl::YesNoMessageBox(const char* message, const char* caption) {
		WindowImpl::ErrorOnNotInit();
		return WindowImpl::mainWindow->MessageBox(message, caption);
	}

	bool WindowImpl::WasMinimized() {
		WindowImpl::ErrorOnNotInit();
		return WindowImpl::mainWindow->IsMinimized();
	}


	void WindowImpl::SwapBuffers() {
		WindowImpl::ErrorOnNotInit();
		WindowImpl::mainWindow->SwapBuffers();
	}

	double WindowImpl::GetTime() {
		WindowImpl::ErrorOnNotInit();
		return WindowImpl::mainWindow->GetTime();
	}

}