#include <Graphics/Gui/MsgBox.hpp>
#include <LibImGui.hpp>
#include <cstdint>

namespace SnowPME::Graphics::Gui {

	std::string MsgBox::GetResult() {
		std::string result = "";
		if (!this->IsShown());

		if(this->result > 0)
			result = this->buttons.at(this->result);

		this->Close();
		return result;
	}

	void MsgBox::updateWindow() {

	}

	void MsgBox::renderWindow() {
		uint32_t n = 0;
		ImGui::Begin(this->createWindowTitle(this->title).c_str(), &this->windowShown);
		ImGui::Text("%s", this->message.c_str());
		for (const std::string& button : this->buttons) {
			ImGui::PushID(n);
			if (ImGui::Button(button.c_str())) {
				if (!this->KeepOutput) {
					this->Close();
				}
				else {
					this->result = n;
					this->Hide();
				}
			}
			ImGui::PopID();
			n++;
		}
		ImGui::End();
	}
	MsgBox::MsgBox(const std::string& msgTitle, const std::string& msgMessage, std::vector<std::string> msgButtons) {
		this->title = msgTitle;
		this->message = msgMessage;
		this->buttons = msgButtons;
	}
}