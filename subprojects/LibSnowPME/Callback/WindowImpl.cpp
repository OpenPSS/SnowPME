#include <Callback/WindowImpl.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace SnowPME::Graphics;

namespace SnowPME::Callback {

	void WindowImpl::PollEvents() {
		//TODO: Should probably replace with a 'capture' system
	}

	bool WindowImpl::WasClosed() {
		return false;
	}

	bool WindowImpl::YesNoMessageBox(const char* message, const char* caption) {
		return Window::GetMainWindow()->ShowMessageBox(message, caption);
	}

	bool WindowImpl::WasMinimized() {
		return false;
	}

	void WindowImpl::SwapBuffers() {
		Window::GetMainWindow()->SwapBuffers();
	}

	double WindowImpl::GetTime() {
		return Window::GetMainWindow()->GetTime();
	}

}