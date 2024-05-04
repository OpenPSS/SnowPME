#ifndef SNOW_PME_WINDOW_H
#define SNOW_PME_WINDOW_H 1
#include <cstdint>
#include <string>
#include <SDL.h>

namespace SnowPME::Graphics {
	class Window {
	private:
		SDL_Window* sdlWindow = nullptr;
		SDL_GLContext glCtx = nullptr;
		std::string openGlVersion;
		float refreshRate;
		void onResized();
	public:
		Window(int height, int width, const std::string& title);
		void SwapBuffers();
		void Vsync(uint32_t frameTaken);
		uint32_t GetTime();
		void PollEvents();
		bool IsMinimized();
		bool ShouldClose();
		bool MessageBox(const std::string& message, const std::string&  caption);

		SDL_Window* GetSdlWindow();
		SDL_GLContext GetGlCtx();
		
		~Window();
	};
}

#endif