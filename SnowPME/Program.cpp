#include <Program.hpp>
#include <LibShared.hpp>
#include <LibSnowPME.hpp>

#include <cxxopts.hpp>
using namespace Shared;
using namespace Shared::Debug;
using namespace Shared::String;

using namespace SnowPME::Runtime;
using namespace SnowPME::Graphics;
using namespace SnowPME::Graphics::Gui;

namespace SnowPME {


	void Program::progThreadFunc() {
		std::shared_ptr<Window> window = Window::GetMainWindow();
		if (window == nullptr) return;

		if (!window->IsOpenGLInitalized()) {
			window->InitOpenGL();
		}

		Logger::Debug("Running mono program ...");
		if (ProgramSelectWindow::Programs.HasSelectedProgram()) {
			Application::LoadApplication(this->programPath, window);
		}
	}

	void Program::guiThreadFunc() {
		std::shared_ptr<Window> window = Window::GetMainWindow();
		if (window == nullptr) return;

		if (!window->IsOpenGLInitalized()) {
			window->InitOpenGL();
		}

		Logger::Debug("Running GUI render loop.");
		while (!gui->Done()) {
			gui->RenderGui();
		}
		
		this->programPath = ProgramSelectWindow::Programs.SelectedProgram().programPath;
		this->progThreadFunc();
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

		auto gamePath = opts["path"].as_optional<std::string>();
		if(gamePath.has_value()) {
			this->programPath = gamePath.value();
			this->guiThread = std::thread(&Program::progThreadFunc, this);
		} else {
			bool showGui = true;

			if(opts.count("gui")) {
				showGui = opts["gui"].as<bool>();
			}

			if (showGui) {
				Logger::Debug("Setting up Gui.");
				this->gui = std::make_unique<SnowGui>(Window::GetMainWindow());

				Logger::Debug("Initalizing main window.");
				ProgramSelectWindow* mainWindow = new ProgramSelectWindow();
				mainWindow->Register();

				this->guiThread = std::thread(&Program::guiThreadFunc, this);

				while (this->guiThread.joinable()) {

					if (!this->gui->Done()) {
						this->gui->UpdateGui();
					}

					if (Application::IsRunning()) {
						Application::CheckEvent();
					}
				}
			}

		}
	}

	Program::~Program() {}
}