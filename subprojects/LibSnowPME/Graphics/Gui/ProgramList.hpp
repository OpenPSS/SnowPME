#ifndef SNOW_PME_PROGRAMLIST_H
#define SNOW_PME_PROGRAMLIST_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
#include <LibShared.hpp>
#include <vector>
#include <string>
#include <atomic>

namespace SnowPME::Graphics::Gui {

	typedef struct ProgramEntry {
		std::string label = "";
		std::string programPath = "";
		bool selected = false;
		bool enabled = true;
	} ProgramEntry;

	class ProgramList {
	private:
		ProgramEntry selectedProgram;
		std::vector<ProgramEntry> programs;
		std::atomic<bool> hasSelectedProgram = false;

		ProgramEntry& addMenuItem(std::string menuName, std::string programPath);
		void parsePsmFolder(std::string psmFolderPath);
	public:
		void Refresh();
		void RenderProgramList();
		void SpecifyProgramByPath(std::string gameFolder);
		ProgramEntry& SelectedProgram();
		bool HasSelectedProgram();
	};

};
#endif