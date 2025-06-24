#include <Graphics/Gui/InstallGamePackageWindow.hpp>
#include <LibImGui.hpp>
#include <pfd/portable-file-dialogs.h>

namespace SnowPME::Graphics::Gui {
	
	void InstallGamePackageWindow::browseGame() {
		pfd::open_file* filepicker = new pfd::open_file("Open Package File", "/", { "Package Files (.pkg)", "*.pkg" }, pfd::opt::none);

		if (!filepicker->result().empty()) {
			this->gameFile = filepicker->result().at(0);
		}

		delete filepicker;
	}

	void InstallGamePackageWindow::installGame() {
		ASSERT(true);
	}

}