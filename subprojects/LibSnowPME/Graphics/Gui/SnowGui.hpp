#ifndef SNOW_PME_SNOWGUI_H
#define SNOW_PME_SNOWGUI_H 1
#include <Graphics/Window.hpp>
#include <atomic>

namespace SnowPME::Graphics::Gui {
	class SnowGui {
	private:
		std::shared_ptr<Window> window = nullptr;
		std::atomic<bool> done = false;

		void setupImgui();
	public:
		SnowGui(std::shared_ptr<Window> guiWindow);
		~SnowGui();

		bool Done();
		void UpdateGui();
		void RenderGui();

		void NewFrame();
		void EndFrame();
	};
}

#endif
