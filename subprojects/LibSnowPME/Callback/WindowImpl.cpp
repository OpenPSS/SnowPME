#include <Callback/WindowImpl.hpp>
#include <LibShared.hpp>
#include <cassert>

using namespace Shared::Debug;
using namespace SnowPME::Graphics;

namespace SnowPME::Callback {

	void WindowImpl::PollEvents() {
		Logger::Todo(__FUNCTION__);
	}

	bool WindowImpl::WasClosed() {
		Logger::Todo(__FUNCTION__);
		return false;
	}

	bool WindowImpl::YesNoMessageBox(const char* message, const char* caption) {
		return Window::GetMainWindow()->ShowMessageBox(message, caption);
	}

	bool WindowImpl::WasMinimized() {
		Logger::Todo(__FUNCTION__);
		return false;
	}

	void WindowImpl::SwapBuffers() {
		Window::GetMainWindow()->SwapBuffers();
	}

	double WindowImpl::GetTime() {
		return Window::GetMainWindow()->GetTime();
	}

}