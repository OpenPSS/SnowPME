#ifndef SNOW_PME_RUNTIME_INIT_H
#define SNOW_PME_RUNTIME_INIT_H 1
#include <string>
#include <Graphics/Window.hpp>
#include <sdl/sdl.h>

namespace SnowPME::Runtime
{
	class Application {
	private:
		std::string appMainDirectory;

		static SDL_Thread* psmGameThread;
		static Application* runningApplication;

		static int initCallbacks(Graphics::Window* oglWindow);
		static int __cdecl runGameThread(void* app);

	public:
		Application(const std::string& gameFolder);
		void RunPssMain();

		static void LoadApplication(const std::string& gameFolder, Graphics::Window* window);
	};
}

#endif