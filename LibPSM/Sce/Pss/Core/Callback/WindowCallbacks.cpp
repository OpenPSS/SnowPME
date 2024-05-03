#include <Sce/Pss/Core/Callback/WindowCallbacks.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>

namespace Sce::Pss::Core::Callback {
	using namespace Shared::Debug;

	void   (*WindowCallbacks::swapBufferCallback)(void) = nullptr;
	double (*WindowCallbacks::getTimeCallback)(void) = nullptr;
	void   (*WindowCallbacks::pollEventsCallback)(void) = nullptr;
	bool   (*WindowCallbacks::wasClosedCallback)(void) = nullptr;
	bool   (*WindowCallbacks::wasMinimizedCallback)(void) = nullptr;
	bool   (*WindowCallbacks::showYesNoDialogCallback)(const char*, const char*) = nullptr;

	void WindowCallbacks::Init(void (*swapBuffers)(void),
		double (*getTime)(void),
		void (*pollEventsCallback)(void),
		bool (*wasClosedCallback)(void),
		bool (*wasMinimizedCallback)(void),
		bool (*showYesNoDialogCallback)(const char*, const char*)) {
		
		WindowCallbacks::swapBufferCallback = swapBuffers;
		WindowCallbacks::getTimeCallback = getTime;
		WindowCallbacks::pollEventsCallback = pollEventsCallback;
		WindowCallbacks::wasClosedCallback = wasClosedCallback;
		WindowCallbacks::wasMinimizedCallback = wasMinimizedCallback;
		WindowCallbacks::showYesNoDialogCallback = showYesNoDialogCallback;

		WindowCallbacks::isInitalized = true;
	}

	int WindowCallbacks::SwapBuffers() {
		errorOnNotInitalized();
		swapBufferCallback();
		return PSM_ERROR_NO_ERROR;
	}

	double WindowCallbacks::GetTime() {
		errorOnNotInitalized();
		return getTimeCallback();
	}

	void WindowCallbacks::PollEvents() {
		errorOnNotInitalized();
		pollEventsCallback();
	}

	bool WindowCallbacks::IsClosed() {
		errorOnNotInitalized();
		return wasClosedCallback();
	}

	bool WindowCallbacks::IsMinimized() {
		errorOnNotInitalized();
		return wasMinimizedCallback();
	}

	bool WindowCallbacks::YesNoDialog(std::string message, std::string caption) {
		errorOnNotInitalized();
		return showYesNoDialogCallback(message.c_str(), caption.c_str());
	}



}