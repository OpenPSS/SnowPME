#ifndef SNOW_PME_DEMOWINDOW_H
#define SNOW_PME_DEMOWINDOW_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
namespace SnowPME::Graphics::Gui {
	class DemoWindow : public ImGuiWindow {
	protected:
		void updateWindow();
		void renderWindow();
	};
}
#endif