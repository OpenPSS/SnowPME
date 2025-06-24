#include <SDL2/SDL.h>
#include <Graphics/Window.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>
#include <thread>
#include <string>
#include <LibPSM.hpp>

using namespace Shared::Debug;

namespace SnowPME::Graphics {
	std::shared_ptr<Window> Window::mainWindow = nullptr;
	std::shared_ptr<Window> Window::GetMainWindow() {
		return Window::mainWindow;
	}

	Window::Window(int height, int width, const std::string& title) {
		ASSERT(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) == 0);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES | SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		this->sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL|SDL_RENDERER_PRESENTVSYNC);
		ASSERT(this->sdlWindow != nullptr);

		int displayIndex = SDL_GetWindowDisplayIndex(this->sdlWindow);
		SDL_DisplayMode mode;
		
		if (SDL_GetDisplayMode(displayIndex, 0, &mode) != 0) {
			Logger::Warn("Could not get display mode! SDL_Error: "+ std::string(SDL_GetError()));
			mode.refresh_rate = 60;
		}

		this->refreshRate = mode.refresh_rate;

	}

	bool Window::IsOpenGLInitalized() {
		return this->glInitalized;
	}

	void Window::InitOpenGL() {
		Logger::Debug("Initalizing OpenGL");

		this->glCtx = SDL_GL_CreateContext(this->sdlWindow);
		ASSERT(this->glCtx != nullptr);
		ASSERT(gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress));

		SDL_GL_MakeCurrent(this->sdlWindow, this->glCtx);
		SDL_GL_SetSwapInterval(1);

		onResized();

		this->openGlVersion = std::string((char*)glGetString(GL_VERSION));
		this->glInitalized = true;
	}

	SDL_Window* Window::GetSdlWindow() {
		return this->sdlWindow;
	}

	SDL_GLContext Window::GetGlCtx() {
		return this->glCtx;
	}

	void Window::onResized() {
		int windowWidth = 0;
		int windowHeight = 0;
		SDL_GetWindowSize(this->sdlWindow, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
	}

	uint32_t Window::GetTime() {
		return SDL_GetTicks();
	}


	void Window::SwapBuffers() {
		SDL_GL_SwapWindow(this->sdlWindow);
	}

	void Window::Vsync(uint32_t frameTaken) {
		int32_t frameTime = 1000 / this->refreshRate;
        int32_t frameDelay = frameTime - frameTaken;
        if (frameDelay > 0) {
            SDL_Delay(frameDelay);
        }
	}
	
	bool Window::ShowMessageBox(const std::string& message, const std::string& caption) {
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
		data.window = this->sdlWindow;
		data.title = caption.c_str();
		data.message = message.c_str();
		data.numbuttons = 2;
		data.buttons = buttonData;
		data.colorScheme = nullptr;

		int buttonSelected = -1;
		SDL_ShowMessageBox(&data, &buttonSelected);

		return buttonSelected;
	}

	Window::~Window() {
		if(this->glCtx != nullptr) SDL_GL_DeleteContext(this->glCtx);
		if(this->sdlWindow != nullptr) SDL_DestroyWindow(this->sdlWindow);
		SDL_Quit();
	}

	void Window::Create(int height, int width, const std::string& title) {
		Window::mainWindow = std::make_shared<Graphics::Window>(height, width, title);
	}

	void Window::Delete() {
		mainWindow->~Window();
		Window::mainWindow = nullptr;
	}
}
