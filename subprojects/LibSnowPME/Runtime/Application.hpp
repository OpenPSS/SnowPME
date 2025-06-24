#ifndef SNOW_PME_RUNTIME_INIT_H
#define SNOW_PME_RUNTIME_INIT_H 1
#include <string>
#include <Graphics/Window.hpp>
#include <thread>
#include <memory>

namespace SnowPME::Runtime
{
	class Application {
	private:
		static std::shared_ptr<Application> runningApplication;
		std::string appMainDirectory;
		std::shared_ptr<Graphics::Window> appWindow = nullptr;
		std::thread appThread;

		static int initCallbacks(std::shared_ptr<Graphics::Window> window);

	public:
		Application(const std::string& gameFolder, std::shared_ptr<Graphics::Window> window);
		void RunPssMain();
		static bool IsRunning();
		static void CheckEvent();
		static void LoadApplication(const std::string& gameFolder, std::shared_ptr<Graphics::Window> window);
	};
}

#endif