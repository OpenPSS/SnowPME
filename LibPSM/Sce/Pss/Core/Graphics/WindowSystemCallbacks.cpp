#include <Sce/Pss/Core/Graphics/WindowSystemCallbacks.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	bool WindowSystemCallbacks::isInitalized = false;
	void (*WindowSystemCallbacks::swapBufferCallback)(void) = nullptr;
	double (*WindowSystemCallbacks::getTimeCallback)(void) = nullptr;


	void WindowSystemCallbacks::Init(void (*swapBuffers)(void), double (*getTime)(void)) {
		WindowSystemCallbacks::swapBufferCallback = swapBuffers;
		WindowSystemCallbacks::getTimeCallback = getTime;
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

}