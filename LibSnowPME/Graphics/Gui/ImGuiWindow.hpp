#ifndef SNOW_PME_IMGUI_WINDOW_H
#define SNOW_PME_IMGUI_WINDOW_H 1
#include <list>
#include <string>

namespace SnowPME::Graphics::Gui {
	class ImGuiWindow {
	private:
		std::string uuid = "";
		static std::list<ImGuiWindow*> registeredWindows;
	protected:
		bool windowOpen = true;
		bool windowShown = true;
		std::string createWindowTitle(std::string windowTitle);
		virtual void updateWindow() = 0;
		virtual void renderWindow() = 0;
	public:
		ImGuiWindow();
		~ImGuiWindow();
		void Show();
		void Display();
		void Hide();
		void Close();
		void Register();
		void Unregister();

		bool IsShown();
		bool IsOpen();

		static void ProcessWindows();
		static void RegisterWindow(ImGuiWindow* windowToRegister);
		static void UnregisterWindow(ImGuiWindow* registeredWindow);
	};

}
#endif
