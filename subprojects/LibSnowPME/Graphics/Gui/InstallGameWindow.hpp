#ifndef SNOW_PME_INSTALLGAMEWINDOW_H
#define SNOW_PME_INSTALLGAMEWINDOW_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
#include <LibShared.hpp>
#include <string>

namespace SnowPME::Graphics::Gui {
	class InstallGameWindow : public ImGuiWindow {
	protected:
		char zRIF[0x5000];
		std::string rifFile = "";
		std::string gameFile = "";

		bool useZrif = true;
		bool useRif = false;

		Shared::Threading::ProgressTracker progress;

		virtual void browseRif();
		virtual void browseGame();
		virtual void installGame() = NULL;
		void renderWindow();
	public:
		InstallGameWindow();
	};
}
#endif