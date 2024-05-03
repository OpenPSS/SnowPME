#ifndef SNOW_PME_RUNTIME_INIT_H
#define SNOW_PME_RUNTIME_INIT_H 1
#include <string>
#include <Graphics/Window.hpp>

namespace SnowPME::Runtime
{
	class Init {
	private:
		static int initCallbacks(Graphics::Window* oglWindow);
		static std::string gameFolder;
	public:
		static void LoadApplication(std::string gameFolder, Graphics::Window* window);
		static void StartApplication();
	};
}

#endif