#include <Sce/Pss/Core/Callback/WindowCallbacks.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Callback {

	bool WindowCallbacks::isInitalized = false;

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
		if (WindowCallbacks::isInitalized) {
			swapBufferCallback();
			return PSM_ERROR_NO_ERROR;
		}
		else {
			throw std::exception("WindowCallbacks is not initalized,");
		}
	}

	double WindowCallbacks::GetTime() {
		if (WindowCallbacks::isInitalized) {
			return getTimeCallback();
		}
		else {
			throw std::exception("WindowCallbacks is not initalized,");
		}
	}

	void WindowCallbacks::PollEvents() {
		if (WindowCallbacks::isInitalized) {
			pollEventsCallback();
		}
		else {
			throw std::exception("WindowCallbacks is not initalized,");
		}
	}

	bool WindowCallbacks::IsClosed() {
		if (WindowCallbacks::isInitalized) {
			return wasClosedCallback();
		}
		else {
			throw std::exception("WindowCallbacks is not initalized,");
		}
	}

	bool WindowCallbacks::IsMinimized() {
		if (WindowCallbacks::isInitalized) {
			return wasMinimizedCallback();
		}
		else {
			throw std::exception("WindowCallbacks is not initalized,");
		}
	}

	bool WindowCallbacks::YesNoDialog(std::string message, std::string caption) {
		if (WindowCallbacks::isInitalized) {
			return showYesNoDialogCallback(message.c_str(), caption.c_str());
		}
		else {
			throw std::exception("WindowCallbacks is not initalized,");
		}
	}



}