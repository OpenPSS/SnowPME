#include <Graphics/Gui/InstallGameFolderWindow.hpp>
#include <Graphics/Gui/ProgramSelectWindow.hpp>
#include <LibShared.hpp>
#include <filesystem>
#include <vector>

using namespace Shared::Debug;

namespace SnowPME::Graphics::Gui {

	void InstallGameFolderWindow::installGame() {
		std::string rootDirectory = this->gameFile;
		std::string applicationFolder = std::filesystem::path(rootDirectory).append("Application").string();
		if (!std::filesystem::exists(applicationFolder)) applicationFolder = std::filesystem::path(rootDirectory).append("RO").append("Application").string();
		std::string installDirectory = Shared::Config::PsmApps;
		Logger::Debug("Recursive copying " + rootDirectory + " the to " + installDirectory);

		if (std::filesystem::exists(applicationFolder)) {
			// first calculate how many files

			// reset the progress bar
			this->progress.Reset(1);
			this->progress.SetShowProgress(true);

			// do the actual copy of files to new directory
			for (const std::filesystem::directory_entry& ent : std::filesystem::recursive_directory_iterator(rootDirectory, std::filesystem::directory_options::skip_permission_denied)) {

				std::string srcFile = ent.path().string();
				std::string relFile = srcFile.substr(std::filesystem::path(rootDirectory).parent_path().string().length()+1);
				std::string dstFile = std::filesystem::path(installDirectory).append(relFile).string();

				Logger::Debug("dstFile: " + dstFile + " // " + relFile + " // " + srcFile);

				if (std::filesystem::exists(dstFile)) {
					continue;
				}
				else if (ent.is_directory()) {
					Logger::Debug("Creating directory: " + dstFile);
					std::filesystem::create_directories(dstFile);
				}
				else if (ent.is_regular_file()) {
					
					Logger::Debug("Copying: " + srcFile + " to " + dstFile);
					std::filesystem::copy_file(srcFile, dstFile);
				}

			}

			this->progress.Increment();

			ProgramSelectWindow::Programs.Refresh();
		}		
	}
}