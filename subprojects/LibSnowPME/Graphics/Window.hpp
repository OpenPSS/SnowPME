#ifndef SNOW_PME_WINDOW_H
#define SNOW_PME_WINDOW_H 1
#include <cstdint>
#include <string>
#include <thread>
#include <memory>
#include <atomic>

#include <Graphics/ImGuiBackend.hpp>
#include <SDL.h>

namespace SnowPME::Graphics {
	class Window {
	private:
		static std::shared_ptr<Window> mainWindow;
		SDL_Window* sdlWindow = nullptr;
		SDL_GLContext glCtx = nullptr;
		std::string openGlVersion = "";
		std::atomic<bool> glInitalized = false;

		float refreshRate;
		void onResized();

		bool tryGl();
		bool tryGles();
	public:
		std::unique_ptr<ImGuiBackend> Backend = nullptr;

		Window(int height, int width, const std::string& title);

		void SwapBuffers();
		void Vsync(uint32_t frameTaken);
		uint32_t GetTime();

		void ShowErrorMessage(const std::string& error, const std::string& caption);
		bool ShowMessageBox(const std::string& message, const std::string& caption);
		void InitOpenGL();
		bool IsOpenGLInitalized();

		SDL_Window* GetSdlWindow();
		SDL_GLContext GetGlCtx();
		
		static std::shared_ptr<Window> GetMainWindow();
		static void Create(int height, int width, const std::string& title);
		static void Delete();

		~Window();
	};
}

#endif