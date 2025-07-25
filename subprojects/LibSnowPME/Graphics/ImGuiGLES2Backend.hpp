#include <Graphics/ImGuiBackend.hpp>

namespace SnowPME::Graphics {
	class ImGuiGLES2Backend : public ImGuiBackend {
	public:
		void NewFrame();
		void EndFrame();
		void Init();
		void Term();
		std::string Name();
	};
}