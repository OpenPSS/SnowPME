#include <LibImGui.hpp>
#include <Graphics/Gui/SnowGui.hpp>
#include <Graphics/Gui/ImGuiWindow.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace SnowPME::Graphics::Gui {
	void SnowGui::setupImgui() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui_ImplSDL2_InitForOpenGL(this->window->GetSdlWindow(), this->window->GetGlCtx());
		ImGui_ImplOpenGL2_Init();
	}

	void SnowGui::UpdateGui() {

		SDL_Event event;
		
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				this->done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window->GetSdlWindow()))
				this->done = true;
		}

		if (!ImGuiWindow::HasOpenWindows()) {
			this->done = true;
		}

	}

	void SnowGui::RenderGui() {
		uint32_t frameStart = this->window->GetTime();
		this->NewFrame();
		ImGuiWindow::ProcessWindows();
		this->EndFrame();
		uint32_t frameEnd = this->window->GetTime();
		this->window->Vsync(frameEnd - frameStart);
	}

	void SnowGui::NewFrame() {
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void SnowGui::EndFrame() {
		ImGui::Render();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		window->SwapBuffers();
	}

	bool SnowGui::Done() {
		return this->done;
	}

	SnowGui::SnowGui(std::shared_ptr<Window> guiWindow) {
		this->window = guiWindow;
		this->setupImgui();
	}

	SnowGui::~SnowGui() {
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}


}