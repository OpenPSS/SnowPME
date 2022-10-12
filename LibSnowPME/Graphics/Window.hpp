#ifndef SNOW_PME_INIT_H
#define SNOW_PME_INIT_H 1
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SnowPME::Graphics {
	class Window {
	private:
		GLFWwindow* window;
		std::string openGlVersion;
	public:
		Window(int height, int width, std::string title);
		bool ShouldClose();
		~Window();
	};
}

#endif