#ifndef SNOW_PME_IMGUI_WINDOW_H
#define SNOW_PME_IMGUI_WINDOW_H 1
#include <list>
namespace SnowPME::Graphics::Gui {
	class ImGuiWindow {
	private:
		static std::list<ImGuiWindow*> registeredWindows;
	protected:
		bool windowOpen = true;
		virtual void updateWindow() = NULL;
		virtual void renderWindow() = NULL;
	public:
		ImGuiWindow();
		~ImGuiWindow();
		void ShowWindow();
		void DisplayWindow();
		void CloseWindow();

		static void ProcessWindows();
		static void RegisterWindow(ImGuiWindow* windowToRegister);
		static void UnregisterWindow(ImGuiWindow* registeredWindow);
	};

}
#endif