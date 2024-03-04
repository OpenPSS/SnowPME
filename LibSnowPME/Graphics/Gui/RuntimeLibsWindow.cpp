#include <Sce/Pss/Core/Mono/Security.hpp>
#include <Sce/Pss/Core/Mono/PsmDlls.hpp>
#include <Graphics/Gui/RuntimeLibsWindow.hpp>
#include <Graphics/Gui/MsgBox.hpp>
#include <LibShared.hpp>
#include <LibImGui.hpp>
#include <filesystem>
#include <pfd/portable-file-dialogs.h>

using namespace Shared;
using namespace Sce::Pss::Core::Mono;
namespace SnowPME::Graphics::Gui {
	void RuntimeLibsWindow::checkDlls() {
		this->mscorlibValid				= Security::VerifyDll(Config::MscorlibPath(), PsmDlls::PssSystemFileEnum::MSCORLIB);
		this->systemValid				= Security::VerifyDll(Config::SystemLibPath(), PsmDlls::PssSystemFileEnum::SYSTEM);
		this->scePlayStationCoreValid	= Security::VerifyDll(Config::PsmCoreLibPath(), PsmDlls::PssSystemFileEnum::SCE_PLAYSTATON_CORE);
	}

	void RuntimeLibsWindow::installDll(PsmDlls::PssSystemFileEnum whatDll) {

		pfd::open_file* filepicker = new pfd::open_file("Open Runtime DLL", "/", { "Dynamic Link Libraries (.dll)", "*.dll" }, pfd::opt::none);
		
		if (!filepicker->result().empty()) {
			std::string dllPath = filepicker->result().at(0);

			if (Security::VerifyDll(dllPath, whatDll)) {
				std::string outputDir = "";

				switch (whatDll) {
					case PsmDlls::PssSystemFileEnum::MSCORLIB:
						outputDir = Config::MscorlibPath();
						break;
					case PsmDlls::PssSystemFileEnum::SYSTEM:
						outputDir = Config::SystemLibPath();
						break;
					case PsmDlls::PssSystemFileEnum::SCE_PLAYSTATON_CORE:
						outputDir = Config::PsmCoreLibPath();
						break;
					case PsmDlls::PssSystemFileEnum::NONE:
					default:
						return;
				}

				// create runtime folders ..
				std::filesystem::create_directories(std::filesystem::path(outputDir).remove_filename());

				// copy file to output location ..
				std::filesystem::copy_file(dllPath, outputDir, std::filesystem::copy_options::overwrite_existing);

			}
			else {
				MsgBox* box = new MsgBox("Fail", "Runtime library file:  " + std::filesystem::path(dllPath).filename().string() + " is corrupt or invalid.", { "OK" } );
				box->KeepOutput = false;
				box->Register();
			}
		}

		delete filepicker;
		checkDlls();
	}

	void RuntimeLibsWindow::updateWindow() {

	}
	void RuntimeLibsWindow::renderWindow() {
		uint32_t n = 0;

		ImGui::Begin(this->createWindowTitle("Runtime Libraries").c_str(), &this->windowOpen);
		ImGui::Text("SnowPME requires the following libraries from the \"PlayStation Mobile Runtime Package\"");

		ImGui::Text("mscorlib.dll:");
		ImGui::SameLine();
		if (!this->mscorlibValid) ImGui::TextColored(ImVec4(1, 0, 0, 1), "NOT FOUND"); else ImGui::TextColored(ImVec4(0, 1, 0, 1), "INSTALLED");
		ImGui::SameLine();

		ImGui::PushID(n++);
		if (ImGui::Button("Browse")) {
			installDll(PsmDlls::PssSystemFileEnum::MSCORLIB);
		}
		ImGui::PopID();

		ImGui::Text("System.dll:");
		ImGui::SameLine();
		if (!this->systemValid) ImGui::TextColored(ImVec4(1, 0, 0, 1), "NOT FOUND"); else ImGui::TextColored(ImVec4(0, 1, 0, 1), "INSTALLED");
		ImGui::SameLine();

		ImGui::PushID(n++);
		if (ImGui::Button("Browse")) {
			installDll(PsmDlls::PssSystemFileEnum::SYSTEM);
		}
		ImGui::PopID();

		ImGui::Text("Sce.PlayStation.Core.dll:");
		ImGui::SameLine();
		if (!this->scePlayStationCoreValid) ImGui::TextColored(ImVec4(1, 0, 0, 1), "NOT FOUND"); else ImGui::TextColored(ImVec4(0, 1, 0, 1), "INSTALLED");
		ImGui::SameLine();

		ImGui::PushID(n++);	
		if (ImGui::Button("Browse")) {
			installDll(PsmDlls::PssSystemFileEnum::SCE_PLAYSTATON_CORE);
		}
		ImGui::PopID();

		ImGui::Text("For instructions on how to obtain this can be found below:");

		if (ImGui::TreeNode("Obtaining from a PlayStation Vita")) {
			if (ImGui::TreeNode("Modded Vita; pull with VitaShell")) {
				ImGui::Text("Your vita *must* have Henkaku installed for this method, (see vita.hacks.guide).");
				ImGui::Text(" - Ensure the last version (2.01) of the \"PlayStation Mobile Runtime Package\" is installed.");
				ImGui::Text(" - Open the VitaShell application, and navigate to \"ux0:/patch/\"");
				ImGui::Text(" - Find the \"PCSI00011\" directory, and press the TRIANGLE button on it and select \"Open Decrypted\"");
				ImGui::Text(" - Find the \"dll\" directory, and press the SQUARE button on it.");
				ImGui::Text(" - Press TRIANGLE and select \"Copy\".");
				ImGui::Text(" - Navigate to \"ux0:/data\".");
				ImGui::Text(" - Press TRIANGLE and select \"Paste\".");
				ImGui::Text(" - Transfer the \"ux0:/data/dll\" directory to your Computer via FTP or USB.");
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Stock Vita; pull with Content Manager")) {
				ImGui::Text("TODO : explain how to do this");
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Obtaining from PlayStation Mobile App on Android")) {
			ImGui::Text("TODO : explain how to do this");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Obtaining from the PlayStation Mobile SDK")) {
			ImGui::Text("The PlayStation Mobile SDK includes the required files, they can be found at the following locations:");
			ImGui::Text(" - mscorlib.dll is located at : %%SCE_PSM_SDK%%/mono/lib/mono/2.1/mscorlib.dll");
			ImGui::Text(" - System.dll is located at : %%SCE_PSM_SDK%%/mono/lib/mono/2.1/System.dll");
			ImGui::Text(" - Sce.PlayStation.Core.dll is located at : %%SCE_PSM_SDK%%/mono/lib/psm/Sce.PlayStation.Core.dll");
			ImGui::TreePop();
		}

		ImGui::End();

	}

	RuntimeLibsWindow::RuntimeLibsWindow() {
		checkDlls();
	}
	RuntimeLibsWindow::~RuntimeLibsWindow() {

	}
}