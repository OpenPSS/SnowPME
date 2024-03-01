#include <Graphics/Gui/ImGuiWindow.hpp>
namespace SnowPME::Graphics::Gui {
	std::list<ImGuiWindow*> ImGuiWindow::registeredWindows = std::list<ImGuiWindow*>();

	void ImGuiWindow::ShowWindow() {
		this->windowOpen = true;
	}
	void ImGuiWindow::CloseWindow() {
		this->windowOpen = false;
	}

	void ImGuiWindow::DisplayWindow() {
		if (this->windowOpen) {
			this->updateWindow();
			this->renderWindow();
		}
	}

	ImGuiWindow::ImGuiWindow() {
		this->ShowWindow();
	}

	ImGuiWindow::~ImGuiWindow() {
		this->CloseWindow();
		ImGuiWindow::UnregisterWindow(this);
	}

	void ImGuiWindow::RegisterWindow(ImGuiWindow* windowToRegister) {
		if (windowToRegister != nullptr)
			ImGuiWindow::registeredWindows.push_back(windowToRegister);
	}

	void ImGuiWindow::UnregisterWindow(ImGuiWindow* registeredWindow) {
		if (registeredWindow != nullptr)
			ImGuiWindow::registeredWindows.remove(registeredWindow);
	}

	void ImGuiWindow::ProcessWindows() {
		for (ImGuiWindow* win : ImGuiWindow::registeredWindows) {
			win->DisplayWindow();
		}
	}
}