#ifndef SNOW_PME_INSTALLGAMEPACKAGEWINDOW_H
#define SNOW_PME_INSTALLGAMEPACKAGEWINDOW_H 1
#include <Graphics/Gui/InstallGameWindow.hpp>
#include <string>

namespace SnowPME::Graphics::Gui {
	class InstallGamePackageWindow : public InstallGameWindow {
	protected:
		void browseGame();
		void installGame();
	};
}
#endif