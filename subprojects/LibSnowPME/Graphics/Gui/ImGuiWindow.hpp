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
		std::string createWindowTitle(const std::string& windowTitle);
		virtual void renderWindow() = NULL;
		virtual void updateWindow();
		virtual void onWindowClose();
	public:
		ImGuiWindow();
		~ImGuiWindow();
		virtual void Show();
		virtual void Display();
		virtual void Hide();
		virtual void Close();
		virtual void Register();
		virtual void Unregister();

		virtual bool IsShown();
		virtual bool IsOpen();

		static void ProcessWindows();
		static void RegisterWindow(ImGuiWindow* windowToRegister);
		static void UnregisterWindow(ImGuiWindow* registeredWindow);
	};

}
#endif
