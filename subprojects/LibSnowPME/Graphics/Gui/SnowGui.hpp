#ifndef SNOW_PME_SNOWGUI_H
#define SNOW_PME_SNOWGUI_H 1
#include <Graphics/Window.hpp>

namespace SnowPME::Graphics::Gui {
	class SnowGui {
	private:
		std::shared_ptr<Window> window = nullptr;

		// gui state 
		bool done = false;

		void setupImgui();
		void updateGui();
		void renderGui();
	public:
		SnowGui(std::shared_ptr<Window> guiWindow);
		~SnowGui();

		void RunMainLoop();

		void NewFrame();
		void EndFrame();
	};
}

#endif
