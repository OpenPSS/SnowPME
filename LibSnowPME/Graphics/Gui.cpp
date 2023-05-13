#include <LibPSM.hpp>
#include <Graphics/Gui.hpp>
#include <Runtime/Init.hpp>
#include <LibShared.hpp>

using namespace SnowPME::Runtime;

namespace SnowPME::Graphics {
	static Window* mainWindow;
	void Gui::Init() {
		mainWindow = new Window(Shared::Config::ScreenHeight(0), Shared::Config::ScreenWidth(0), "- SnowPME -");
		//AppGlobals::SetPsmMainWindow(mainWindow);
		Shared::Config::ReadConfig("SnowPME.cfg");

		Init::LoadApplication("Test");
		Init::StartApplication();
	}
}
