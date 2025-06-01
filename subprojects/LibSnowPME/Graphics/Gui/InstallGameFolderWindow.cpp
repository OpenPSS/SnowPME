#include <Graphics/Gui/InstallGameFolderWindow.hpp>
#include <LibShared.hpp>
#include <filesystem>
#include <vector>

using namespace Shared::String;

namespace SnowPME::Graphics::Gui {

	void InstallGameFolderWindow::installGame() {
		std::string rootDirectory = this->gameFile;
		std::string applicationFolder = Path::Combine(rootDirectory, "Application");
		if(!std::filesystem::exists(applicationFolder)) applicationFolder = Path::Combine(Path::Combine(rootDirectory, "RO"), "Application");
		std::string installDirectory = Shared::Config::PsmApps;

		if (std::filesystem::exists(applicationFolder)) {
			// first calculate how many files
			int total = 0;

			for (const std::filesystem::directory_entry& ent : std::filesystem::recursive_directory_iterator(rootDirectory)) { 
				total++;
			}

			// reset the progress bar
			this->progress.Reset(total);
			this->progress.SetShowProgress(true);

			// do the actual copy of files to new directory
			for (const std::filesystem::directory_entry& ent : std::filesystem::recursive_directory_iterator(rootDirectory)) {
				std::string relFile = ent.path().string().substr(std::filesystem::path(rootDirectory).parent_path().string().length());
				std::string dstFile = Path::Combine(installDirectory, relFile);

				if (ent.is_directory()) {
					std::filesystem::create_directories(dstFile);
				}
				else if (ent.is_regular_file()) {
					std::filesystem::copy_file(ent.path().string(), dstFile);
				}

				this->progress.Increment();
			}
		}		
	}
}