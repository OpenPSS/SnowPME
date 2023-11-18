#include <Graphics/Window.hpp>

#include <LibShared.hpp>
#include <glad/glad.h>
#include <sdl/SDL.h>

#include <LibPSM.hpp>

using namespace Shared::Debug;

namespace SnowPME::Graphics {

	Window::Window(int height, int width, std::string title) {
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
			Logger::Error("Failed to initalize SDL2.");
			throw std::exception("Failed to initalize SDL2.");
		};
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
		
		if (this->window == NULL) {
			Logger::Error("Failed to create SDL window.");
			throw std::exception("Failed to create SDL window.");
		}

		this->glCtx = SDL_GL_CreateContext(this->window);

		if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
			Logger::Error("Failed to initalize GL.");
			throw std::exception("Failed to initalize GL.");
		}

		onResized();

		this->openGlVersion = std::string((char*)glGetString(GL_VERSION));
	}
	
	void Window::onResized() {
		int windowWidth = 0;
		int windowHeight = 0;
		SDL_GetWindowSize(this->window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
	}

	void Window::PollEvents() {
		SDL_Event event;
		SDL_PollEvent(&event);

	}
	double Window::GetTime() {
		return (double)SDL_GetTicks();
	}

	bool Window::IsMinimized() {
		return false; //glfwGetWindowAttrib(window, GLFW_ICONIFIED);
	}

	void Window::SwapBuffers() {
		SDL_GL_SwapWindow(this->window);
	}
	
	bool Window::ShouldClose() {
		return false; //glfwWindowShouldClose(this->window);
	}

	bool Window::MessageBox(const char* message, const char* caption) {
		SDL_MessageBoxButtonData buttonData[2];
		memset(buttonData, 0, sizeof(SDL_MessageBoxButtonData) * 2);

		buttonData[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
		buttonData[0].text = "Yes";
		buttonData[0].buttonid = true;

		buttonData[1].flags = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
		buttonData[1].text = "No";
		buttonData[1].buttonid = false;

		SDL_MessageBoxData data;
		memset(&data, 0, sizeof(SDL_MessageBoxData));

		data.flags = SDL_MESSAGEBOX_INFORMATION;
		data.window = this->window;
		data.title = caption;
		data.message = message;
		data.numbuttons = 2;
		data.buttons = buttonData;
		data.colorScheme = nullptr;

		int buttonSelected = -1;
		SDL_ShowMessageBox(&data, &buttonSelected);

		return buttonSelected;
	}

	Window::~Window() {
		if(this->glCtx != nullptr) SDL_GL_DeleteContext(this->glCtx);
		if(this->window != nullptr)	SDL_DestroyWindow(this->window);
		SDL_Quit();
	}

}