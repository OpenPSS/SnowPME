#ifndef SNOW_PME_RUNTIMELIBSWINDOW_H
#define SNOW_PME_RUNTIMELIBSWINDOW_H 1

#include <Graphics/Gui/ImGuiWindow.hpp>
#include <string>

namespace SnowPME::Graphics::Gui {
	class RuntimeLibsWindow : public ImGuiWindow {
	private:
		bool mscorlibValid = false;
		bool systemValid = false;
		bool scePlayStationCoreValid = false;
		void checkDlls();
	protected:
		void updateWindow();
		void renderWindow();
	public:
		RuntimeLibsWindow();
		~RuntimeLibsWindow();
	};
}

#endif