#ifndef SNOW_PME_MSGBOX_H
#define SNOW_PME_MSGBOX_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
#include <vector>
namespace SnowPME::Graphics::Gui {
	class MsgBox : public ImGuiWindow {
	private:
		int result = -1;
		std::string title;
		std::string message;
		std::vector<std::string> buttons;
	protected:
		void updateWindow();
		void renderWindow();
	public:
		MsgBox(const std::string& msgTitle, const std::string& msgMessage, std::vector<std::string>msgButtons);
		std::string GetResult();
		bool KeepOutput = true;
	};
}

#endif