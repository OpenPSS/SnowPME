#include <Graphics/Gui/SnowGui.hpp>
#include <Graphics/Gui/MainWindow.hpp>
#include <Graphics/Gui/RuntimeLibsWindow.hpp>
#include <LibImGui.hpp>

namespace SnowPME::Graphics::Gui {

	void MainWindow::createMenuBar() {
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Install")) {
				if (ImGui::MenuItem("Install Runtime Package")) {
					RuntimeLibsWindow* runtimeLibs = new RuntimeLibsWindow();
					runtimeLibs->Register();
				}
				if (ImGui::MenuItem("Install Game from PKG File")) {

				}
				if (ImGui::MenuItem("Install Game from Folder")) {

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Game")) {
				if (ImGui::MenuItem("Backup SaveData")) {

				}
				if (ImGui::MenuItem("Delete SaveData")) {

				}
				if (ImGui::MenuItem("Delete Game")) {

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Configure")) {
				if (ImGui::MenuItem("Set Account ID")) {

				}
				if (ImGui::MenuItem("Change Username")) {

				}
				if (ImGui::MenuItem("Change Target Runtime Implementation")) {

				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
	void MainWindow::updateWindow() {

	}
	void MainWindow::renderWindow() {
		this->createMenuBar();

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);

		ImGui::Begin("Game Selector", &this->windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);
		ImGui::Text("No games installed.");
		ImGui::End();
	}


}