#include <Graphics/Gui/SnowGui.hpp>
#include <Graphics/Gui/ProgramSelectWindow.hpp>
#include <Graphics/Gui/RuntimeLibsWindow.hpp>
#include <Graphics/Gui/InstallGamePackageWindow.hpp>
#include <Graphics/Gui/InstallGameFolderWindow.hpp>
#include <Graphics/Gui/ConfigurationWindow.hpp>
#include <LibImGui.hpp>
#include <LibShared.hpp>
#include <Runtime/Application.hpp>

using namespace SnowPME::Runtime;

namespace SnowPME::Graphics::Gui {
	void ProgramSelectWindow::createMenuBar() {
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Install")) {
				if (ImGui::MenuItem("Install Runtime Package")) {
					RuntimeLibsWindow* runtimeLibs = new RuntimeLibsWindow();
					runtimeLibs->Register();
				}
				if (ImGui::MenuItem("Install Game from Package File")) {
					InstallGamePackageWindow* gamePkgInstall = new InstallGamePackageWindow();
					gamePkgInstall->Register();
				}
				if (ImGui::MenuItem("Install Game from Folder")) {
					InstallGameFolderWindow* gameFolderInstall = new InstallGameFolderWindow();
					gameFolderInstall->Register();
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
			if (ImGui::BeginMenu("Configuration")) {
				ConfigurationWindow* configWindow = new ConfigurationWindow();
				configWindow->Register();
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void ProgramSelectWindow::updateWindow() {
		if (this->Programs.HasSelectedProgram()) {
			ProgramEntry entry = this->Programs.SelectedProgram();
			this->Close();

			Application::LoadApplication(entry.programPath, Window::GetMainWindow());
		}

	}

	void ProgramSelectWindow::renderWindow() {
		this->createMenuBar();

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);

		ImGui::Begin(this->createWindowTitle("Game Selector").c_str() , &this->windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);
		Programs.RenderProgramList();
		ImGui::End();
	}


}