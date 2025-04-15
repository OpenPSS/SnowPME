#ifndef SNOW_PME_RUNTIME_INIT_H
#define SNOW_PME_RUNTIME_INIT_H 1
#include <string>
#include <Graphics/Window.hpp>
#include <thread>

namespace SnowPME::Runtime
{
	class Application {
	private:
		std::string appMainDirectory;
		Graphics::Window* appWindow;

		static Application* runningApplication;

		static int initCallbacks(Graphics::Window* window);
		

	public:
		Application(const std::string& gameFolder, Graphics::Window* window);
		void RunPssMain();
		static void LoadApplication(const std::string& gameFolder, Graphics::Window* window);
	};
}

#endif