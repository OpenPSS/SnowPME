#include <Graphics/Gui/ImGuiWindow.hpp>
namespace SnowPME::Graphics::Gui {
	std::list<ImGuiWindow*> ImGuiWindow::registeredWindows = std::list<ImGuiWindow*>();

	void ImGuiWindow::Show() {
		this->windowOpen = true;
	}
	void ImGuiWindow::Close() {
		this->windowOpen = false;
	}

	void ImGuiWindow::Display() {
		if (this->IsOpen()) {
			this->updateWindow();
			this->renderWindow();
		}
	}

	bool ImGuiWindow::IsOpen() {
		return this->windowOpen;
	}

	ImGuiWindow::ImGuiWindow() {
		this->Show();
	}

	ImGuiWindow::~ImGuiWindow() {
		this->Close();
		this->Unregister();
	}

	void ImGuiWindow::Register() {
		ImGuiWindow::RegisterWindow(this);
	}

	void ImGuiWindow::Unregister() {
		ImGuiWindow::UnregisterWindow(this);
	}

	// static functions

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
			if (win->IsOpen()) {
				win->Display();
			}
			else {
				delete win;
				return;
			}
		}
	}
}