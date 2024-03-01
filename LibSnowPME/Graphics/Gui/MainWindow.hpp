#ifndef SNOW_PME_MAINWINDOW_H
#define SNOW_PME_MAINWINDOW_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
namespace SnowPME::Graphics::Gui {

	class MainWindow : public ImGuiWindow {
	private:
		void createMenuBar();
	protected:
		void updateWindow();
		void renderWindow();
	};

}
#endif