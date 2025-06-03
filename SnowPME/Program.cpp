#include "Program.hpp"
#include <LibShared.hpp>
#include <LibSnowPME.hpp>
#include <LibPSM.hpp>

#include <cxxopts.hpp>
using namespace Shared;
using namespace Shared::Debug;
using namespace Shared::String;
using namespace SnowPME::Runtime;
using namespace Sce::Pss::Core::Event;

namespace SnowPME {

	void Program::startMonoApplication(const std::string& gamePath) {
		// run program
		Application::LoadApplication(gamePath, this->window);
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
		Graphics::Window::create(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME - ");
		this->window = std::make_shared<Graphics::Window>(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME - ");

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
				Graphics::Gui::SnowGui gui(this->window);

				Logger::Debug("Initalizing main window.");
				Graphics::Gui::ProgramSelectWindow* mainWindow = new Graphics::Gui::ProgramSelectWindow();
				mainWindow->Register();
				
				Logger::Debug("Running GUI main loop.");
				gui.RunMainLoop();
			}
		}
	}

	Program::~Program() {}
}