#include <Graphics/Gui/InstallGamePackageWindow.hpp>
#include <LibImGui.hpp>
#include <pfd/portable-file-dialogs.h>

namespace SnowPME::Graphics::Gui {
	
	void InstallGamePackageWindow::browsePkg() {
		pfd::open_file* filepicker = new pfd::open_file("Open Package File", "/", { "Package Files (.pkg)", "*.pkg" }, pfd::opt::none);

		if (!filepicker->result().empty()) {
			this->packageFile = filepicker->result().at(0);
		}

		delete filepicker;
	}

	void InstallGamePackageWindow::browseRif() {
		pfd::open_file* filepicker = new pfd::open_file("Open Rights Information File", "/", { "Rights Information Files (.rif)", "*.rif" }, pfd::opt::none);

		if (!filepicker->result().empty()) {
			this->rifFile = filepicker->result().at(0);
		}

		delete filepicker;
	}
	
	void InstallGamePackageWindow::updateWindow() {

	}

	void InstallGamePackageWindow::renderWindow() {
		uint32_t n = 0;
		ImGui::Begin(this->createWindowTitle("Install Game Package").c_str(), &this->windowOpen);
		
		ImGui::Text("Specify license by: ");
		ImGui::SameLine();
		if (ImGui::Checkbox("zRIF", &this->useZrif))
			this->useRif = false;

		ImGui::SameLine();
		if (ImGui::Checkbox("RIF", &this->useRif))
			this->useZrif = false;
		
		if (this->useZrif) {
			ImGui::PushItemWidth(-1);
			ImGui::InputTextWithHint("##zrifEntry", "Enter zRIF string", this->zRIF, sizeof(this->zRIF));
		}
		if (this->useRif) {
			
			ImGui::Text("FAKE.RIF: %s", this->rifFile.c_str());
			ImGui::SameLine();

			ImGui::PushID(n++);
			if (ImGui::Button("Browse")) {
				this->browseRif();
			}
			ImGui::PopID();
		}
		ImGui::Text("PACKAGE FILE: %s", this->packageFile.c_str());
		ImGui::SameLine();

		ImGui::PushID(n++);
		if (ImGui::Button("Browse")) {
			this->browsePkg();
		}
		ImGui::PopID();

		if ((this->useRif || this->useZrif)) {
			if (ImGui::Button("Install Game")) {

			}
		}


		ImGui::End();
	}
	InstallGamePackageWindow::InstallGamePackageWindow() {
		memset(this->zRIF, 0x00, sizeof(this->zRIF));
	}
}