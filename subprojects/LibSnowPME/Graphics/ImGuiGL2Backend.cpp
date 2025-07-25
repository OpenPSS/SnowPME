#include <Graphics/ImGuiGL2Backend.hpp>
#include <LibImGui.hpp>
#include <string>

namespace SnowPME::Graphics {

	void ImGuiGL2Backend::Init() {
		ImGui_ImplOpenGL2_Init();
	}

	void ImGuiGL2Backend::Term() {
		ImGui_ImplOpenGL2_Shutdown();
	}

	void ImGuiGL2Backend::NewFrame() {
		ImGui_ImplOpenGL2_NewFrame();
	}

	void ImGuiGL2Backend::EndFrame() {
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	std::string ImGuiGL2Backend::Name() {
		return "OpenGL";
	}

}