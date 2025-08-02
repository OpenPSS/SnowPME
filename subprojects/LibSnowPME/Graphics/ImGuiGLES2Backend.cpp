#include <Graphics/ImGuiGLES2Backend.hpp>
#include <LibImGui.hpp>

namespace SnowPME::Graphics {
	
	void ImGuiGLES2Backend::Init() {
		ImGui_ImplGLES2_Init("#version 100");
	}

	void ImGuiGLES2Backend::Term() {
		ImGui_ImplGLES2_Shutdown();
	}

	void ImGuiGLES2Backend::NewFrame() {
		ImGui_ImplGLES2_NewFrame();
	}

	void ImGuiGLES2Backend::EndFrame() {
		ImGui_ImplGLES2_RenderDrawData(ImGui::GetDrawData());
	}

	std::string ImGuiGLES2Backend::Name() {
		return "GLES";
	}
}