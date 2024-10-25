#ifndef SNOW_PME_INSTALLGAMEFOLDERWINDOW_H
#define SNOW_PME_INSTALLGAMEFOLDERWINDOW_H 1
#include <Graphics/Gui/InstallGameWindow.hpp>
#include <string>

namespace SnowPME::Graphics::Gui {
	class InstallGameFolderWindow : public InstallGameWindow {
	protected:
		void installGame();
	};
}

#endif