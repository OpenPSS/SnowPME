#include <Graphics/Callback.hpp>

namespace SnowPME::Graphics {

	bool Callback::isInitalized = false;
	Window* Callback::mainWindow = nullptr;

	void Callback::Init(Window* window) {
		Callback::mainWindow = window;

		Callback::isInitalized = true;
	}

	void Callback::PollEvents() {
		if (!Callback::isInitalized) {
			throw std::exception("GraphicsCallback is not initalized!");
		}
		Callback::mainWindow->PollEvents();
	}

	bool Callback::WasClosed() {
		if (!Callback::isInitalized) {
			throw std::exception("GraphicsCallback is not initalized!");
		}
		return Callback::mainWindow->ShouldClose();
	}

	bool Callback::YesNoMessageBox(const char* message, const char* caption) {
		if (!Callback::isInitalized) {
			throw std::exception("GraphicsCallback is not initalized!");
		}
		return Callback::mainWindow->MessageBox(message, caption);
	}

	bool Callback::WasMinimized() {
		if (!Callback::isInitalized) {
			throw std::exception("GraphicsCallback is not initalized!");
		}
		return Callback::mainWindow->IsMinimized();
	}


	void Callback::SwapBuffers() {
		if (!Callback::isInitalized) {
			throw std::exception("GraphicsCallback is not initalized!");
		}
		Callback::mainWindow->SwapBuffers();
	}

	double Callback::GetTime() {
		if (!Callback::isInitalized) {
			throw std::exception("GraphicsCallback is not initalized!");
		}
		return Callback::mainWindow->GetTime();
	}

}