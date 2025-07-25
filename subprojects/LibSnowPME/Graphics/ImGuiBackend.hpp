#ifndef SNOW_PME_IMGUIBACKEND_H
#define SNOW_PME_IMGUIBACKEND_H 1
#include <string>
namespace SnowPME::Graphics {
	class ImGuiBackend {
	public:
		ImGuiBackend() = default;
		virtual ~ImGuiBackend() = default;
		virtual void NewFrame() = 0;
		virtual void EndFrame() = 0;
		virtual void Init() = 0;
		virtual void Term() = 0;
		virtual std::string Name() = 0;
	};
}


#endif