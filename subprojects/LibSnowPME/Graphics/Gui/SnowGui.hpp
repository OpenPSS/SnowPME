#ifndef SNOW_PME_SNOWGUI_H
#define SNOW_PME_SNOWGUI_H 1

#include <Graphics/Window.hpp>
#include <Graphics/Gui/MainWindow.hpp>
namespace SnowPME::Graphics::Gui {
	class SnowGui {
	private:
		Window* window;

		// gui state 
		bool done = false;

		void setupImgui();
		void updateGui();
		void renderGui();
	public:
		SnowGui(Window* guiWindow);
		~SnowGui();

		void RunMainLoop();

		void NewFrame();
		void EndFrame();
	};
}

#endif
