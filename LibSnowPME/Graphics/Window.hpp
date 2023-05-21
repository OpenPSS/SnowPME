#ifndef SNOW_PME_WINDOW_H
#define SNOW_PME_WINDOW_H 1
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SnowPME::Graphics {
	class Window {
	private:
		GLFWwindow* window;
		std::string openGlVersion;
		static void swapBuffersCallback();
	public:
		Window(int height, int width, std::string title);
		void SwapBuffers();
		bool ShouldClose();
		~Window();
	};
}

#endif