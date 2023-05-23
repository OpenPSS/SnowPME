#include <Graphics/Callback.hpp>

namespace SnowPME::Graphics {

	bool Callback::isInitalized = false;
	Window* Callback::mainWindow = nullptr;

	void Callback::Init(Window* window) {
		Callback::mainWindow = window;

		Callback::isInitalized = true;
	}

	void Callback::SwapBuffers() {
		if (!Callback::isInitalized) {
			throw new std::exception("GraphicsCallback is not initalized!");
		}
		Callback::mainWindow->SwapBuffers();
	}

	double Callback::GetTime() {
		if (!Callback::isInitalized) {
			throw new std::exception("GraphicsCallback is not initalized!");
		}
		return Callback::mainWindow->GetTime();
	}

}