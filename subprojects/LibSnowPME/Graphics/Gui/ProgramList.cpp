#include <Graphics/Gui/ProgramList.hpp>
#include <LibCXML.hpp>
#include <LibPSM.hpp>
#include <LibImGui.hpp>
#include <LibShared.hpp>
#include <filesystem>

using namespace LibCXML;
using namespace Shared;
using namespace Shared::String;
using namespace Sce::Pss::Core::Metadata;

namespace SnowPME::Graphics::Gui {

	void ProgramList::addMenuItem(std::string menuName, std::string programPath) {
		ProgramEntry progEntry;
		progEntry.label = menuName + "##" + StringUtil::CreateRandomString(10);
		progEntry.programPath = programPath;
		progEntry.selected = false;
		progEntry.enabled = true;

		this->programs.push_back(progEntry);
	}

	void ProgramList::parsePsmFolder(std::string psmFolderPath) {
		if(std::filesystem::exists(psmFolderPath)) {
			for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator(psmFolderPath)) {
				if (dirEntry.is_directory()) {
					std::string fname = dirEntry.path().filename().string();
					std::string programPath = dirEntry.path().string();

					std::string appInfoPath = Path::Combine(Path::Combine(programPath, "Application"), "app.info");
					if (!std::filesystem::exists(appInfoPath)) appInfoPath = Path::Combine(Path::Combine(Path::Combine(programPath, "RO"), "Application"), "app.info");

					if (std::filesystem::exists(appInfoPath)) {
						AppInfo appInfo(new CXMLElement(appInfoPath, "PSMA"));
						std::string shortName = appInfo.GetLocaleValue(appInfo.Names, Config::SystemLanguage);
						if (shortName != "") {
							this->addMenuItem(shortName, programPath);
							continue;
						}
					}

					this->addMenuItem(fname, programPath);
				}
			}

		}
	}

	ProgramList::ProgramList() {
		this->Refresh();
	}

	void ProgramList::Refresh() {
		this->programs.clear();
		this->hasSelectedProgram = false;
		this->parsePsmFolder(Config::PsmApps);
	}


	ProgramList::~ProgramList() {
		this->programs.clear();
		this->hasSelectedProgram = false;
	}


	bool ProgramList::HasSelectedProgram() {
		return this->hasSelectedProgram;
	}

	ProgramEntry ProgramList::SelectedProgram() {
		return this->selectedProgram;
	}

	void ProgramList::RenderProgramList() {
		if (this->programs.empty()) {
			ImGui::MenuItem("No programs installed", nullptr, nullptr, false);
		}
		else {
			for (ProgramEntry progEntry : this->programs) {
				if (ImGui::MenuItem(progEntry.label.c_str(), nullptr, &progEntry.selected, progEntry.enabled)) {
					this->selectedProgram = progEntry;
					this->hasSelectedProgram = true;
				}
			}
		}
	}
}