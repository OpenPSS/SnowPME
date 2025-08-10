#include <Graphics/Gui/InstallGamePackageWindow.hpp>
#include <Graphics/Gui/ProgramSelectWindow.hpp>
#include <Graphics/Window.hpp>
#include <Graphics/Gui/MsgBox.hpp>

#include <LibImGui.hpp>
#include <LibShared.hpp>
#include <pfd/portable-file-dialogs.h>
#include <memory>
#include <fstream>
#include <filesystem>
using namespace Shared;
using namespace Shared::Debug;
using namespace Shared::Package;
using namespace Shared::String;

namespace SnowPME::Graphics::Gui {
	
	std::string InstallGamePackageWindow::windowTitle() {
		return "Install Package File";
	}
	std::string InstallGamePackageWindow::selectionFormatString() {
		return "PKG: %s";
	}

	void InstallGamePackageWindow::browseGame() {
		pfd::open_file filepicker("Open Package File", "/", { "Package Files (.pkg)", "*.pkg" }, pfd::opt::none);

		if (!filepicker.result().empty()) {
			this->gameFile = filepicker.result().at(0);
		}

	}


	void InstallGamePackageWindow::installGame() {
		std::unique_ptr<PackageExtractor> extractor = std::make_unique<PackageExtractor>(this->gameFile);

		if (!extractor->GetErrorMessage().empty()) {
			MsgBox* box = new MsgBox("Failed to install package.", extractor->GetErrorMessage(), { "OK" });
			box->KeepOutput = false;
			box->Register();
			return;
		}
		
		Logger::Debug("Extracting: " + extractor->ContentId() + " (" + extractor->TitleId() + ")");
		std::string extractPath = std::filesystem::path(Config::GetPsmAppsFolder()).append(extractor->TitleId()).string();
		std::filesystem::create_directories(extractPath);

		int err = extractor->ExtractFolder("contents/", extractPath, &this->progress);
		if (err != PKG_ERROR_NO_ERROR) {
			MsgBox* box = new MsgBox("Failed to install package.", extractor->GetErrorMessage(), {"OK"});
			box->KeepOutput = false;
			box->Register();

			return;
		}

		/*
		* """promote""" the game
		*/

		std::filesystem::path systemDir = std::filesystem::path(extractPath).append("System");
		std::filesystem::path documentsDir = std::filesystem::path(extractPath).append("Documents");
		std::filesystem::path tempDir = std::filesystem::path(extractPath).append("Temp");
		std::filesystem::path licenseDir = std::filesystem::path(extractPath).append("License");

		std::filesystem::create_directories(systemDir);
		std::filesystem::create_directories(documentsDir);
		std::filesystem::create_directories(tempDir);
		std::filesystem::create_directories(licenseDir);

		// write content id file
		std::fstream stream(std::filesystem::path(systemDir).append("content_id"));
		char cid[0x30] = { 0 };
		strncpy(cid, extractor->ContentId().c_str(), sizeof(cid));
		stream.write(cid, sizeof(cid));
		stream.close();

		// copy rif to license folder
		if (this->useRif && std::filesystem::exists(this->rifFile)) {
			std::filesystem::copy_file(this->rifFile, std::filesystem::path(licenseDir).append("FAKE.rif"), std::filesystem::copy_options::overwrite_existing);
		}

		ProgramSelectWindow::Programs.Refresh();

	}

}