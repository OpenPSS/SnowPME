#ifndef SNOW_PME_INSTALLGAMEPACKAGEWINDOW_H
#define SNOW_PME_INSTALLGAMEPACKAGEWINDOW_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
#include <string>
namespace SnowPME::Graphics::Gui {
	class InstallGamePackageWindow : public ImGuiWindow {
	private:
		char zRIF[0x5000];
		std::string rifFile = "";
		std::string packageFile = "";

		bool useZrif = true;
		bool useRif = false;

		void browsePkg();
		void browseRif();
	protected:
		void updateWindow();
		void renderWindow();
	public:
		InstallGamePackageWindow();
	};
}
#endif