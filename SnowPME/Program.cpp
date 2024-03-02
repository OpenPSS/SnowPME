#include "Program.hpp"
#include <LibShared.hpp>
#include <LibSnowPME.hpp>
using namespace Shared;
using namespace Shared::Debug;
using namespace SnowPME::Runtime;

namespace SnowPME {
	void Program::startMonoApplication(std::string gamePath) {
		// load the mono executable
		Init::LoadApplication(gamePath, this->window);

		// start executing the mono executable
		Init::StartApplication();
	}
	Program::Program() {
		Logger::Debug("Reading config file.");
		Config::ReadConfig("SnowPME.cfg");

		Logger::Debug("Opening Window.");
		this->window = new Graphics::Window(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME - ");

		Logger::Debug("Setting up Gui.");
		this->gui = new Graphics::Gui::SnowGui(this->window);

		Logger::Debug("Initalizing main window.");
		this->mainWindow = new Graphics::Gui::MainWindow();
		this->mainWindow->Register();

		Logger::Debug("Running GUI main loop.");
		this->gui->RunMainLoop();
	}

	Program::~Program() {
		delete this->window;
		delete this->gui;
	}
}