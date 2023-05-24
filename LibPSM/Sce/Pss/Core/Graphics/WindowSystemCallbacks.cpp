#include <Sce/Pss/Core/Graphics/WindowSystemCallbacks.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	bool WindowSystemCallbacks::isInitalized = false;

	void   (*WindowSystemCallbacks::swapBufferCallback)(void) = nullptr;
	double (*WindowSystemCallbacks::getTimeCallback)(void) = nullptr;
	void   (*WindowSystemCallbacks::pollEventsCallback)(void) = nullptr;
	bool   (*WindowSystemCallbacks::wasCloseedCallback)(void) = nullptr;
	bool   (*WindowSystemCallbacks::wasMinimizedCallback)(void) = nullptr;

	void WindowSystemCallbacks::Init(void (*swapBuffers)(void),
		double (*getTime)(void),
		void (*pollEvents)(void),
		bool (*wasCloseed)(void),
		bool (*wasMinimized)(void)) {
		
		WindowSystemCallbacks::swapBufferCallback = swapBuffers;
		WindowSystemCallbacks::getTimeCallback = getTime;
		WindowSystemCallbacks::pollEventsCallback = pollEvents;
		WindowSystemCallbacks::wasCloseedCallback = wasCloseed;
		WindowSystemCallbacks::wasMinimizedCallback = wasMinimized;

		WindowSystemCallbacks::isInitalized = true;
	}

	int WindowSystemCallbacks::SwapBuffers() {
		if (WindowSystemCallbacks::isInitalized) {
			swapBufferCallback();
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
			wasCloseedCallback();
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}

	bool WindowSystemCallbacks::IsMinimized() {
		if (WindowSystemCallbacks::isInitalized) {
			wasMinimizedCallback();
		}
		else {
			throw std::exception("WindowSystemCallbacks is not initalized,");
		}
	}


}