#include <Sce/Pss/Core/Graphics/WindowSystemCallbacks.hpp>
#include <Sce/PlayStation/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	bool WindowSystemCallbacks::isInitalized = false;

	void   (*WindowSystemCallbacks::swapBufferCallback)(void) = nullptr;
	double (*WindowSystemCallbacks::getTimeCallback)(void) = nullptr;
	void   (*WindowSystemCallbacks::pollEventsCallback)(void) = nullptr;
	bool   (*WindowSystemCallbacks::wasClosedCallback)(void) = nullptr;
	bool   (*WindowSystemCallbacks::wasMinimizedCallback)(void) = nullptr;
	bool   (*WindowSystemCallbacks::showYesNoDialogCallback)(const char*, const char*) = nullptr;

	void WindowSystemCallbacks::Init(void (*swapBuffers)(void),
		double (*getTime)(void),
		void (*pollEventsCallback)(void),
		bool (*wasClosedCallback)(void),
		bool (*wasMinimizedCallback)(void),
		bool (*showYesNoDialogCallback)(const char*, const char*)) {
		
		WindowSystemCallbacks::swapBufferCallback = swapBuffers;
		WindowSystemCallbacks::getTimeCallback = getTime;
		WindowSystemCallbacks::pollEventsCallback = pollEventsCallback;
		WindowSystemCallbacks::wasClosedCallback = wasClosedCallback;
		WindowSystemCallbacks::wasMinimizedCallback = wasMinimizedCallback;
		WindowSystemCallbacks::showYesNoDialogCallback = showYesNoDialogCallback;

		WindowSystemCallbacks::isInitalized = true;
	}

	int WindowSystemCallbacks::SwapBuffers() {
		if (WindowSystemCallbacks::isInitalized) {
			swapBufferCallback();
			return PSM_ERROR_NO_ERROR;
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}

	double WindowSystemCallbacks::GetTime() {
		if (WindowSystemCallbacks::isInitalized) {
			return getTimeCallback();
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}

	void WindowSystemCallbacks::PollEvents() {
		if (WindowSystemCallbacks::isInitalized) {
			pollEventsCallback();
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}

	bool WindowSystemCallbacks::IsClosed() {
		if (WindowSystemCallbacks::isInitalized) {
			return wasClosedCallback();
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}

	bool WindowSystemCallbacks::IsMinimized() {
		if (WindowSystemCallbacks::isInitalized) {
			return wasMinimizedCallback();
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}

	bool WindowSystemCallbacks::YesNoDialog(std::string message, std::string caption) {
		if (WindowSystemCallbacks::isInitalized) {
			return showYesNoDialogCallback(message.c_str(), caption.c_str());
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}



}