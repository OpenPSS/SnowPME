#include <Graphics/Gui/ConfigurationWindow.hpp>
#include <Graphics/Gui/RuntimeLibsWindow.hpp>

#include <LibImGui.hpp>
#include <LibShared.hpp>
#include <inttypes.h>

using namespace Shared;
using namespace Shared::Debug;

namespace SnowPME::Graphics::Gui {
	static const char* RuntimeImplementationEntries[] = { "PlayStation Vita", "Android", "Windows" };

	void ConfigurationWindow::updateWindow() {
		if (Config::TargetImplementation == RuntimeImplementation::PSVita)	Config::SdkVersion = SDK_2_01_00;
		if (Config::TargetImplementation == RuntimeImplementation::Windows) Config::SdkVersion = SDK_2_00_00;
		if (Config::TargetImplementation == RuntimeImplementation::Android)	Config::SdkVersion = SDK_1_21_02;
	}

	void ConfigurationWindow::renderWindow() {
		ImGui::Begin(this->createWindowTitle("Configuration").c_str(), &this->windowOpen);

		if (ImGui::TreeNodeEx("-- PlayStation Network Account Information --", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Text("Username: ");
			ImGui::SameLine();
			ImGui::InputTextWithHint("##usernameEntry", "Username", Config::Username, sizeof(Config::Username));
			ImGui::Text("AccountID: ");
			ImGui::SameLine();
			ImGui::InputScalar("##accountIdEntry", ImGuiDataType_U64, &Config::AccountId, nullptr, nullptr, "%016" PRIX64, ImGuiInputTextFlags_CharsHexadecimal);
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("-- Runtime Directories --", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Text("Libraries Path: ");
			ImGui::SameLine();
			ImGui::InputTextWithHint("##libPath", "Libraries Path", Config::RuntimeLibPath, sizeof(Config::RuntimeLibPath));
			ImGui::Text("Config Path: ");
			ImGui::SameLine();
			ImGui::InputTextWithHint("##cfgPath", "Config Path",    Config::RuntimeConfigPath, sizeof(Config::RuntimeConfigPath));
			
			if (ImGui::Button("Install PSM Runtime Libraries")) {
				RuntimeLibsWindow* runtimeLibsWindow = new RuntimeLibsWindow();
				runtimeLibsWindow->Register();
			}

			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("-- Mono --", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Text("Profiler Settings: ");
			ImGui::SameLine();
			ImGui::InputTextWithHint("##profilerSettings", "Profiler Settings", Config::ProfilerSettings, sizeof(Config::ProfilerSettings));
			ImGui::Checkbox("SecurityCritical Everywhere", &Config::SecurityCritical);
			ImGui::Checkbox("Enable Debugger", &Config::MonoDebugger);
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("-- SnowPME --", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Text("Game Install Folder: ");
			ImGui::SameLine();
			ImGui::InputTextWithHint("##psmPath", "Game Install Folder", Config::PsmApps, sizeof(Config::PsmApps));
			ImGui::Text("Target Implementation: ");
			ImGui::SameLine();
			ImGui::Combo("##targetImplEntry", reinterpret_cast<int*>(&Config::TargetImplementation), RuntimeImplementationEntries, IM_ARRAYSIZE(RuntimeImplementationEntries));
			ImGui::Text("System Language: ");
			ImGui::SameLine();
			ImGui::InputTextWithHint("##systemLanguage", "en-US", Config::SystemLanguage, sizeof(Config::SystemLanguage));
			ImGui::Checkbox("Enable Debug Logs", &Config::DebugLogging);
			ImGui::TreePop();
		}

		if (ImGui::Button("Save Changes")) {
			this->Close();
		}

		ImGui::End();
	}

	ConfigurationWindow::ConfigurationWindow() {
		Config::ReloadConfig();
	}
	ConfigurationWindow::~ConfigurationWindow() {
		this->onWindowClose();
	}
	void ConfigurationWindow::onWindowClose() {
		Config::SaveConfig();
	}
}