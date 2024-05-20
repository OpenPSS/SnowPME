#include <Graphics/Gui/ImGuiWindow.hpp>
#include <LibImGui.hpp>
#include <mutex>
#include <LibShared.hpp>
using namespace Shared::String;
using namespace Shared::Debug;
namespace SnowPME::Graphics::Gui {

	std::list<ImGuiWindow*> ImGuiWindow::registeredWindows = std::list<ImGuiWindow*>();

	void ImGuiWindow::Show() {
		this->windowOpen = true;
		this->windowShown = true;
	}
	void ImGuiWindow::Close() {
		this->windowOpen = false;
	}

	std::string ImGuiWindow::createWindowTitle(const std::string& windowTitle) {
		return windowTitle + "##" + this->uuid;
	}

	void ImGuiWindow::Display() {
		if (this->IsOpen()) {
			ImGui::PushID(this->uuid.c_str());
			this->updateWindow();
			this->renderWindow();
			ImGui::PopID();
		}
	}

	void ImGuiWindow::Hide() {
		this->windowShown = false;
	}

	bool ImGuiWindow::IsShown() {
		return this->windowShown;
	}
	bool ImGuiWindow::IsOpen() {
		return this->windowOpen;
	}

	ImGuiWindow::ImGuiWindow() {
		this->uuid = StringUtil::CreateRandomString(10);
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
			if (win->IsOpen() && win->IsShown()) {
				win->Display();
			}
			else if(!win->IsOpen()) {
				delete win;
				return;
			}
		}
	}
}