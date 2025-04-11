#include <Graphics/Gui/InstallGameFolderWindow.hpp>
#include <LibShared.hpp>
#include <filesystem>
#include <vector>

using namespace Shared::String;

namespace SnowPME::Graphics::Gui {

	void InstallGameFolderWindow::installGame() {
		std::string rootDirectory = this->gameFile;
		std::string installDirectory = Shared::Config::PsmApps;

		// first calculate how many files
		int total = 0;
		std::filesystem::recursive_directory_iterator iter(rootDirectory);		
		for (std::filesystem::directory_entry ent : iter) total++;

		// reset the progress bar
		this->progress.Reset(total);
		this->progress.SetShowProgress(true);

		// do the actual copy of files to new directory
		iter = std::filesystem::recursive_directory_iterator(rootDirectory);
		for (std::filesystem::directory_entry ent : iter) {
			std::string srcFile = ent.path().string().substr(rootDirectory.length());
			std::string dstFile = Path::Combine(installDirectory, srcFile);

			if (ent.is_directory()) {
				std::filesystem::create_directories(dstFile);
			}
			else if(ent.is_regular_file()) {
				std::filesystem::copy_file(srcFile, dstFile);
			}

			this->progress.Increment();
		}

	}
}