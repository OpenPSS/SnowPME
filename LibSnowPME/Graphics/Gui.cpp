#include <Graphics/Gui.hpp>
#include <Util/Config.hpp>
#include <Runtime/Init.hpp>
#include <Util/AppGlobals.hpp>

using namespace SnowPME::Runtime;
using namespace SnowPME::Util;

namespace SnowPME::Graphics {
	static Window* mainWindow;
	void Gui::Init() {
		mainWindow = new Window(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME -");
		AppGlobals::SetPsmMainWindow(mainWindow);

		Init::LoadApplication("Test");
		Init::StartApplication();
	}
}
