#include <Graphics/Gui/DemoWindow.hpp>
#include <LibImGui.hpp>
namespace SnowPME::Graphics::Gui {
	void DemoWindow::renderWindow() {
		ImGui::ShowDemoWindow(&this->windowOpen);
	}
}