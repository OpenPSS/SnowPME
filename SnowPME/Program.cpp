#include "Program.hpp"
#include <LibShared.hpp>
#include <LibSnowPME.hpp>
#include <cxxopts.hpp>
using namespace Shared;
using namespace Shared::Debug;
using namespace Shared::String;
using namespace SnowPME::Runtime;

namespace SnowPME {
	void Program::startMonoApplication(const std::string& gamePath) {
		// load the mono executable
		Init::LoadApplication(gamePath, this->window);
		// start executing the mono executable
		Init::StartApplication();
	}

	Program::Program(int argc, const char* const* argv) {
		std::string runningFrom = ""; // Path::UpDirectory(std::string(argv[0])); (doesnt work on windows ...)
		Config::ReadConfig(runningFrom, "SnowPME.cfg");
		

		cxxopts::Options options("snowpme", "SnowPME PlayStation Mobile Emulator");

		options.add_options()
			("p,path", "Game Path", cxxopts::value<std::string>())
			("g,gui", "show gui", cxxopts::value<bool>())
			("h,help", "Print usage");

		auto opts = options.parse(argc, argv);

		if(opts.count("help")) {
			std::cout << options.help({""}) << std::endl;
			return;
		}

		Logger::Debug("Opening Window.");
		this->window = new Graphics::Window(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME - ");

		auto gamePath = opts["path"].as_optional<std::string>();
		if(gamePath.has_value()) {
			startMonoApplication(gamePath.value());
		} else {
			bool showGui = true;
			if(opts.count("gui")) {
				showGui = opts["gui"].as<bool>();
			}
			if(showGui) {
				Logger::Debug("Setting up Gui.");
				this->gui = new Graphics::Gui::SnowGui(this->window);

				Logger::Debug("Initalizing main window.");
				Graphics::Gui::MainWindow* mainWindow = new Graphics::Gui::MainWindow();
				mainWindow->Register();

				Logger::Debug("Running GUI main loop.");
				this->gui->RunMainLoop();
			}
		}
	}

	Program::~Program() {
		delete this->window;
		delete this->gui;
	}
}