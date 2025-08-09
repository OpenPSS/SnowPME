#include <Graphics/Gui/InstallGamePackageWindow.hpp>
#include <LibImGui.hpp>
#include <LibShared.hpp>
#include <pfd/portable-file-dialogs.h>
#include <filesystem>
using namespace Shared;
using namespace Shared::Package;

namespace SnowPME::Graphics::Gui {
	
	void InstallGamePackageWindow::browseGame() {
		pfd::open_file filepicker("Open Package File", "/", { "Package Files (.pkg)", "*.pkg" }, pfd::opt::none);

		if (!filepicker.result().empty()) {
			this->gameFile = filepicker.result().at(0);

		}

	}

	void InstallGamePackageWindow::installGame() {
		PackageExtractor extractor;
		std::string installDirectory = Config::GetPsmAppsFolder();
		extractor.ExpandPackage(this->gameFile.c_str(), installDirectory.c_str(), nullptr);
	}

}