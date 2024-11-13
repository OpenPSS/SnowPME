#include <Graphics/Gui/InstallGameWindow.hpp>
#include <pfd/portable-file-dialogs.h>
#include <LibImGui.hpp>

namespace SnowPME::Graphics::Gui {

	void InstallGameWindow::renderWindow() {
		uint32_t n = 0;
		ImGui::Begin(this->createWindowTitle("Install Game").c_str(), &this->windowOpen);

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
		ImGui::Text("GAME: %s", this->gameFile.c_str());
		ImGui::SameLine();

		ImGui::PushID(n++);
		if (ImGui::Button("Browse")) {
			this->browseGame();
		}
		ImGui::PopID();

		if ((this->useRif || this->useZrif) && !this->progress.ShowProgress()) {
			if (ImGui::Button("Install Game")) {
				std::thread installThread = std::thread(&InstallGameWindow::installGame, this);
			}
		}
		else if (this->progress.ShowProgress()) {
			ImGui::ProgressBar(this->progress.Progress());
		}

		ImGui::End();
	}

	void InstallGameWindow::browseGame() {
		pfd::select_folder* filepicker = new pfd::select_folder("Open Game Folder", "/", pfd::opt::none);

		if (!filepicker->result().empty()) {
			this->gameFile = filepicker->result();
		}

		delete filepicker;
	}

	void InstallGameWindow::browseRif() {
		pfd::open_file* filepicker = new pfd::open_file("Open Rights Information File", "/", { "Rights Information Files (.rif)", "*.rif" }, pfd::opt::none);

		if (!filepicker->result().empty()) {
			this->rifFile = filepicker->result().at(0);
		}

		delete filepicker;
	}

	InstallGameWindow::InstallGameWindow() {
		std::memset(this->zRIF, 0, sizeof(InstallGameWindow::zRIF));
	}
}