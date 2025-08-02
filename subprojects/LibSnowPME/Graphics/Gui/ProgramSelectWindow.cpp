#include <Graphics/Gui/SnowGui.hpp>
#include <Graphics/Gui/ProgramSelectWindow.hpp>
#include <Graphics/Gui/RuntimeLibsWindow.hpp>
#include <Graphics/Gui/InstallGamePackageWindow.hpp>
#include <Graphics/Gui/InstallGameFolderWindow.hpp>
#include <Graphics/Gui/ConfigurationWindow.hpp>
#include <LibImGui.hpp>
#include <LibShared.hpp>
#include <Runtime/Application.hpp>
#include <pfd/portable-file-dialogs.h>
using namespace SnowPME::Runtime;

namespace SnowPME::Graphics::Gui {
	ProgramList ProgramSelectWindow::Programs;

	void ProgramSelectWindow::createMenuBar() {
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Install PlayStation Mobile Runtime Package Libraries")) {
					RuntimeLibsWindow* runtimeLibs = new RuntimeLibsWindow();
					runtimeLibs->Register();
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Install Game from Package File")) {
					InstallGamePackageWindow* gamePkgInstall = new InstallGamePackageWindow();
					gamePkgInstall->Register();
				}
				if (ImGui::MenuItem("Install Game from Folder")) {
					InstallGameFolderWindow* gameFolderInstall = new InstallGameFolderWindow();
					gameFolderInstall->Register();
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Run Game from Folder")) {
					pfd::select_folder dirpicker = pfd::select_folder("Open PlayStation Mobile Game Folder", "/", pfd::opt::none);

					if (!dirpicker.result().empty()) {
						Programs.SpecifyProgramByPath(dirpicker.result());
					}
				}
				if (ImGui::MenuItem("Run Portable Executable")) {
					pfd::open_file filepicker = pfd::open_file("Open PlayStation Mobile Executable", "/", { "Portable Executable (.exe)", "*.exe" }, pfd::opt::none);

					if (!filepicker.result().empty()) {
						Programs.SpecifyProgramByPath(filepicker.result().front());
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Game")) {
				if (ImGui::MenuItem("Backup SaveData")) {
					PANIC("Not implemented yet.");
				}
				if (ImGui::MenuItem("Delete SaveData")) {
					PANIC("Not implemented yet.");
				}
				if (ImGui::MenuItem("Delete Game")) {
					PANIC("Not implemented yet.");
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Configuration")) {
				if (ImGui::MenuItem("Configure SnowPME")) {
					ConfigurationWindow* configWindow = new ConfigurationWindow();
					configWindow->Register();
				}
				if (ImGui::MenuItem("Configure Controllers")) {
					PANIC("Not implemented yet.");
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void ProgramSelectWindow::updateWindow() {
		if (Programs.HasSelectedProgram()) {
			this->Close();
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

	ProgramSelectWindow::ProgramSelectWindow() {
		Programs.Refresh();
	}


}