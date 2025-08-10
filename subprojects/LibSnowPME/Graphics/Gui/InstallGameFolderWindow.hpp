#ifndef SNOW_PME_INSTALLGAMEFOLDERWINDOW_H
#define SNOW_PME_INSTALLGAMEFOLDERWINDOW_H 1
#include <Graphics/Gui/InstallGameWindow.hpp>
#include <string>
#include <thread>
#include <memory>

namespace SnowPME::Graphics::Gui {
	class InstallGameFolderWindow : public InstallGameWindow {
	protected:
		std::string windowTitle();
		std::string selectionFormatString();
		void installGame();
	};
}

#endif