#ifndef SNOW_PME_PROGRAMSELECTWINDOW_H
#define SNOW_PME_PROGRAMSELECTWINDOW_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
#include <Graphics/Gui/ProgramList.hpp>

namespace SnowPME::Graphics::Gui {

	class ProgramSelectWindow : public ImGuiWindow {
	private:
		void createMenuBar();
	protected:
		void renderWindow();
		void updateWindow();
	public:
		ProgramList Programs;
	};

}
#endif