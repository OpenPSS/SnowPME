#ifndef SNOW_PME_CONFIGURATIONWINDOW_H
#define SNOW_PME_CONFIGURATIONWINDOW_H 1
#include <Graphics/Gui/ImGuiWindow.hpp>
namespace SnowPME::Graphics::Gui {
	class ConfigurationWindow : public ImGuiWindow {
	protected:
		void onWindowClose();
		void renderWindow();
		void updateWindow();
	public:
		ConfigurationWindow();
		~ConfigurationWindow();
	};
}
#endif