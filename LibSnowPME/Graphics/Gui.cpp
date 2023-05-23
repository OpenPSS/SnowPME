#include <LibPSM.hpp>
#include <Graphics/Gui.hpp>
#include <Runtime/Init.hpp>
#include <LibShared.hpp>

using namespace SnowPME::Runtime;

namespace SnowPME::Graphics {
	void Gui::Init() {
		//AppGlobals::SetPsmMainWindow(mainWindow);
		Shared::Config::ReadConfig("SnowPME.cfg");
		Init::LoadApplication("Test");
		Init::StartApplication();
	}
}
