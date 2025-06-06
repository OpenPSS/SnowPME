#include <Callback/WindowImpl.hpp>

using namespace SnowPME::Graphics;

namespace SnowPME::Callback {
	std::shared_ptr<Window> WindowImpl::mainWindow = nullptr;

	void WindowImpl::Init(std::shared_ptr<Window> window) {
		WindowImpl::mainWindow = window;
		WindowImpl::Impl::isInitalized = true;
	}

	void WindowImpl::PollEvents() {
		WindowImpl::Impl::ErrorOnNotInit();
		WindowImpl::mainWindow->PollEvents();
	}

	bool WindowImpl::WasClosed() {
		WindowImpl::Impl::ErrorOnNotInit();
		return WindowImpl::mainWindow->ShouldClose();
	}

	bool WindowImpl::YesNoMessageBox(const char* message, const char* caption) {
		WindowImpl::Impl::ErrorOnNotInit();
		return WindowImpl::mainWindow->ShowMessageBox(message, caption);
	}

	bool WindowImpl::WasMinimized() {
		WindowImpl::Impl::ErrorOnNotInit();
		return WindowImpl::mainWindow->IsMinimized();
	}


	void WindowImpl::SwapBuffers() {
		WindowImpl::Impl::ErrorOnNotInit();
		WindowImpl::mainWindow->SwapBuffers();
	}

	double WindowImpl::GetTime() {
		WindowImpl::Impl::ErrorOnNotInit();
		return WindowImpl::mainWindow->GetTime();
	}

}