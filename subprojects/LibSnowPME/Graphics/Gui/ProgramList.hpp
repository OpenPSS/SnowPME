#ifndef SNOW_PME_PROGRAMLIST_H
#define SNOW_PME_PROGRAMLIST_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
#include <LibShared.hpp>
#include <vector>
#include <string>
#include <atomic>

namespace SnowPME::Graphics::Gui {

	typedef struct ProgramEntry {
		std::string label;
		std::string programPath;
		bool selected;
		bool enabled;
	} ProgramEntry;

	class ProgramList {
	private:
		ProgramEntry selectedProgram;
		std::vector<ProgramEntry> programs;
		std::atomic<bool> hasSelectedProgram = false;

		void addMenuItem(std::string menuName, std::string programPath);
		void parsePsmFolder(std::string psmFolderPath);
	public:
		void Refresh();
		void RenderProgramList();
		ProgramEntry SelectedProgram();
		bool HasSelectedProgram();
	};

};
#endif