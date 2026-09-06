#include <SDL3/SDL.h>
#include <Graphics/Window.hpp>
#include <Graphics/ImGuiGLES2Backend.hpp>
#include <Graphics/ImGuiGL2Backend.hpp>

#include <LibShared.hpp>
#include <glad/glad.h>
#include <thread>
#include <string>
#include <LibPSM.hpp>
using namespace Shared::Debug;
using namespace Shared::String;


namespace SnowPME::Graphics {
	std::shared_ptr<Window> Window::mainWindow = nullptr;
	std::shared_ptr<Window> Window::GetMainWindow() {
		return Window::mainWindow;
	}

	bool Window::tryGl() {
		Logger::Warn("Cannot use GLES, Falling back on OpenGL Core 3.0");

		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) == true) {
			ASSERT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) == true);
			ASSERT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) == true);
			this->Backend = std::make_unique<ImGuiGL2Backend>();
			return true;
		}
		return false;
	}

	bool Window::tryGles() {
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES) == true) {
			ASSERT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2) == true);
			ASSERT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) == true);
			this->Backend = std::make_unique<ImGuiGLES2Backend>();
			return true;
		}
		return false;
	}

	Window::Window(int height, int width, const std::string& title) {
		ASSERT(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == true);

		ASSERT(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == true);
		ASSERT(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) == true);
		ASSERT(SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) == true);

		ASSERT(SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) == true);
		ASSERT(SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) == true);
		ASSERT(SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) == true);
		ASSERT(SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) == true);

		tryGles();
		this->sdlWindow = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
		if (this->sdlWindow == nullptr) {
			tryGl();

			this->sdlWindow = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
			if (this->sdlWindow == nullptr) {
				PANIC("Cannot create window " + std::string(SDL_GetError()));
			}
		}


		SDL_DisplayID displayIndex = SDL_GetDisplayForWindow(this->sdlWindow);
		ASSERT(displayIndex != 0);

		const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(displayIndex);
		
		if (mode == nullptr) {
			Logger::Warn("Could not get display mode! SDL_Error: "+ std::string(SDL_GetError()));
			this->refreshRate = 60;
		}
		else {
			this->refreshRate = mode->refresh_rate;
		}

	}

	bool Window::IsOpenGLInitalized() {
		return this->glInitalized;
	}

	void Window::InitOpenGL() {
		Logger::Debug("Initalizing OpenGL ...");

		this->glCtx = SDL_GL_CreateContext(this->sdlWindow);
		if (this->glCtx == nullptr) {
			PANIC(SDL_GetError());
		}

		ASSERT(gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) == true);
		ASSERT(SDL_GL_MakeCurrent(this->sdlWindow, this->glCtx) == true);

		if (SDL_GL_SetSwapInterval(1) == false) {
			Logger::Warn("Cannot use SDL_GL_SetSwapInterval " + std::string(SDL_GetError()) + " (Is your monitor unsupported?)");
			Logger::Warn("Screen Tearing may occur, as vsync cannot be used.");
		}


		Logger::Debug("[GLAD] GLVersion.major: " + std::to_string(GLVersion.major));
		Logger::Debug("[GLAD] GLVersion.minor: " + std::to_string(GLVersion.minor));

		int expectedMajor = 0;
		int expectedMinor = 0;

		ASSERT(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &expectedMajor) == true);
		ASSERT(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &expectedMinor) == true);

		if (GLVersion.major < expectedMajor && GLVersion.minor < expectedMinor) {
			PANIC("Could not initalize GLES or OpenGL!\nGot version " + std::to_string(GLVersion.major) + "." + std::to_string(GLVersion.minor) + ", expected atleast : " + std::to_string(expectedMajor) + "." + std::to_string(expectedMinor)+"\nTry updating your graphics drivers?");
		}

		this->openGlVersion = std::string((char*)glGetString(GL_VERSION));
		this->onResized();


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

	void Window::ShowErrorMessage(const std::string& error, const std::string& caption) {
		SDL_MessageBoxData data;
		SDL_MessageBoxButtonData buttons;
		memset(&data, 0x00, sizeof(data));
		memset(&buttons, 0x00, sizeof(buttons));

		buttons.buttonID = 0;
		buttons.flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
		buttons.text = "Ok";

		data.flags = SDL_MESSAGEBOX_ERROR;
		data.window = this->sdlWindow;
		data.title = caption.c_str();
		data.message = error.c_str();
		data.numbuttons = 1;
		data.buttons = &buttons;
		data.colorScheme = nullptr;

		int buttonSelected = -1;

		if (SDL_ShowMessageBox(&data, &buttonSelected) == true) {
			Logger::Error(error);
			Logger::Error("Failed to open messagebox; " + std::string(SDL_GetError()));
		}
	}
	
	bool Window::ShowMessageBox(const std::string& message, const std::string& caption) {
		SDL_MessageBoxButtonData buttonData[2];
		memset(buttonData, 0, sizeof(SDL_MessageBoxButtonData) * 2);

		buttonData[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
		buttonData[0].text = "Yes";
		buttonData[0].buttonID = 1;

		buttonData[1].flags = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
		buttonData[1].text = "No";
		buttonData[1].buttonID = 0;

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
		if (SDL_ShowMessageBox(&data, &buttonSelected) == true) {
			Logger::Info(message);
			Logger::Error("Failed to open messagebox; " + std::string(SDL_GetError()));
		}

		return buttonSelected;
	}

	Window::~Window() {
		if(this->glCtx != nullptr) SDL_GL_DestroyContext(this->glCtx);
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
