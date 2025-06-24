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
		threadRunning = true;

		std::shared_ptr<Window> window = Window::GetMainWindow();
		if (window == nullptr) return;

		if (!window->IsOpenGLInitalized()) {
			window->InitOpenGL();
		}

		Logger::Debug("Running mono program ...");
		if (ProgramSelectWindow::Programs.HasSelectedProgram()) {
			this->exitCode = Application::LoadApplication(this->programPath, window);
		}

		this->threadRunning = false;
	}

	void Program::guiThreadFunc() {
		this->threadRunning = true;
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
		std::string runningFrom = "";
		Config::ReadConfig(runningFrom, "SnowPME.cfg");

		cxxopts::Options options("snowpme", "SnowPME PlayStation Mobile Emulator");

		options.add_options()
			("p,path", "Game Path", cxxopts::value<std::string>())
			("g,gui", "show gui", cxxopts::value<bool>())
			("h,help", "Print usage");

		auto opts = options.parse(argc, argv);

		if (opts.count("help")) {
			std::cout << options.help({ "" }) << std::endl;
			return;
		}

		Logger::Debug("Opening Window.");
		Window::Create(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME - ");

		auto gamePath = opts["path"].as_optional<std::string>();
		if (gamePath.has_value()) {
			this->programPath = gamePath.value();
			this->guiThread = std::thread(&Program::progThreadFunc, this);
		}
		else {
			bool showGui = true;

			if (opts.count("gui")) {
				showGui = opts["gui"].as<bool>();
			}

			if (showGui) {
				Logger::Debug("Setting up Gui.");
				this->gui = std::make_unique<SnowGui>(Window::GetMainWindow());

				Logger::Debug("Initalizing main window.");
				ProgramSelectWindow* mainWindow = new ProgramSelectWindow();
				mainWindow->Register();

				this->guiThread = std::thread(&Program::guiThreadFunc, this);
			}
		}

		// wait for thread start ...
		while (!this->threadRunning) {};

		while (this->threadRunning) {
			if (this->gui != nullptr && !this->gui->Done()) {
				this->gui->UpdateGui();
			}

			if (Application::IsRunning()) {
				Application::CheckEvent();
			}
		}

		Window::Delete();
	}

	Program::~Program() {}

	int Program::ExitCode() {
		return exitCode;
	}
}