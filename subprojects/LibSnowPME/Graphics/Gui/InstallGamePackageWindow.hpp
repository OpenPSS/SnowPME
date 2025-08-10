#ifndef SNOW_PME_INSTALLGAMEPACKAGEWINDOW_H
#define SNOW_PME_INSTALLGAMEPACKAGEWINDOW_H 1
#include <Graphics/Gui/InstallGameWindow.hpp>
#include <string>

namespace SnowPME::Graphics::Gui {
	class InstallGamePackageWindow : public InstallGameWindow {
	private:
	protected:
		std::string windowTitle();
		std::string selectionFormatString();
		void browseGame();
		void installGame();
	};
}
#endif