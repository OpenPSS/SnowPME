#include <Program.hpp>
#include <LibShared.hpp>
#include <LibSnowPME.hpp>

#include <filesystem>
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

		Logger::Debug("Validating config file ...");
		if (Config::ValidateConifg()) {
			
			if (!window->IsOpenGLInitalized()) {
				window->InitOpenGL();
			}

			Logger::Debug("Running mono program ...");
			this->threadRunning = true;
			if (!this->programPath.empty()) {

				if (std::filesystem::is_regular_file(this->programPath)) {
					this->programPath = std::filesystem::path(this->programPath).parent_path().parent_path().string();
				}

				this->exitCode = Application::LoadApplication(this->programPath);
			}

		}


		this->threadRunning = false;
	}

	void Program::guiThreadFunc() {
		std::shared_ptr<Window> window = Window::GetMainWindow();
		if (window == nullptr) return;

		if (!window->IsOpenGLInitalized()) {
			window->InitOpenGL();
		}

		Logger::Debug("Setting up Gui.");
		this->gui = std::make_unique<SnowGui>(Window::GetMainWindow());

		Logger::Debug("Initalizing ProgramSelectWindow.");
		ProgramSelectWindow* progSelectWindow = new ProgramSelectWindow();
		progSelectWindow->Register();

		this->threadRunning = true;

		Logger::Debug("Running GUI render loop.");
		while (!gui->Done()) {
			gui->RenderGui();
		}
		
		if(ProgramSelectWindow::Programs.HasSelectedProgram()) this->programPath = ProgramSelectWindow::Programs.SelectedProgram().programPath;
		this->progThreadFunc();
	}

	Program::Program(int argc, const char* const* argv) {

		// always run from the executable directory;
		std::string runDir;
		if (argc >= 1) runDir = std::filesystem::absolute(argv[0]).parent_path().string();
		if (!std::filesystem::exists(runDir)) runDir = "";

		Config::ReadConfig(runDir, "SnowPME.cfg");
		cxxopts::Options options("snowpme", "SnowPME PlayStation Mobile Emulator");

		options.add_options()
			("g,game", "Game Path", cxxopts::value<std::string>())
			("s,showgui", "Show gui", cxxopts::value<bool>())
			("h,help", "Print usage");

		auto opts = options.parse(argc, argv);

		if (opts.count("help")) {
			std::cout << options.help({ "" }) << std::endl;
			return;
		}

		Logger::Debug("Opening Window.");
		Window::Create(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME - ");
		ApplicationEvent::Init();


		auto gamePath = opts["game"].as_optional<std::string>();
		if (gamePath.has_value()) {
			this->programPath = gamePath.value();
			this->guiThread = std::thread(&Program::progThreadFunc, this);
		}
		else {
			bool showGui = true;

			if (opts.count("showgui")) {
				showGui = opts["showgui"].as<bool>();
			}

			if (showGui) {
				this->guiThread = std::thread(&Program::guiThreadFunc, this);
			}
		}

		// wait for thread start ...
		while (!this->threadRunning) { /**/ };

		while (this->threadRunning) {
			if (this->gui != nullptr && !this->gui->Done()) {
				this->gui->UpdateGui();
			}

			if (Application::IsRunning()) {
				ApplicationEvent::ProcessEvent();
			}
		}

		Window::Delete();
	}

	Program::~Program() {}

	int Program::ExitCode() {
		return exitCode;
	}
}