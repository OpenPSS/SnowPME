#ifndef SNOW_PME_WINDOW_H
#define SNOW_PME_WINDOW_H 1
#include <string>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <thread>
#include <string>

namespace SnowPME::Graphics {
	class Window {
	private:
		SDL_Window* window = nullptr;
		SDL_GLContext glCtx = nullptr;
		std::string openGlVersion;
		void onResized();
	public:
		Window(int height, int width, std::string title);
		void SwapBuffers();
		double GetTime();
		void PollEvents();
		bool IsMinimized();
		bool ShouldClose();
		~Window();
	};
}

#endif