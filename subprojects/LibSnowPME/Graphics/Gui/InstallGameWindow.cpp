#include <Graphics/Gui/InstallGameWindow.hpp>
#include <pfd/portable-file-dialogs.h>
#include <LibImGui.hpp>
#include <cstdlib>
#include <thread>
#include <cstring>

namespace SnowPME::Graphics::Gui {

	std::string InstallGameWindow::selectionFormatString() {
		return "GAME: %s";
	}
	std::string InstallGameWindow::windowTitle() {
		return "Install Game";
	}
	void InstallGameWindow::renderWindow() {
		uint32_t n = 0;
		ImGui::Begin(this->createWindowTitle(this->windowTitle()).c_str(), &this->windowOpen);

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
		ImGui::Text(this->selectionFormatString().c_str(), this->gameFile.c_str());
		ImGui::SameLine();

		ImGui::PushID(n++);
		if (ImGui::Button("Browse")) {
			this->browseGame();
		}
		ImGui::PopID();

		if (!this->progress.ShowProgress()) {
			if (ImGui::Button(this->windowTitle().c_str())) {
				this->installThread = std::make_unique<std::thread>(&InstallGameWindow::installGame, this);
			}
		}
		else if (this->progress.ShowProgress()) {
			ImGui::ProgressBar(this->progress.Progress());
		}

		ImGui::End();
	}

	void InstallGameWindow::browseGame() {
		pfd::select_folder filepicker = pfd::select_folder("Open Game Folder", "/", pfd::opt::none);

		if (!filepicker.result().empty()) {
			this->gameFile = filepicker.result();
		}
	}

	void InstallGameWindow::browseRif() {
		pfd::open_file filepicker = pfd::open_file("Open Rights Information File", "/", { "Rights Information Files (.rif)", "*.rif" }, pfd::opt::none);

		if (!filepicker.result().empty()) {
			this->rifFile = filepicker.result().front();
		}
	}


	InstallGameWindow::~InstallGameWindow() {
		if (this->installThread != nullptr) {
			this->installThread->join();
			this->installThread = nullptr;
		}
	}

	InstallGameWindow::InstallGameWindow() {
		memset(this->zRIF, 0, sizeof(InstallGameWindow::zRIF));
	}
}