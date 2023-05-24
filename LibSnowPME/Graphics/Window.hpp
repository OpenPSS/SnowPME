#ifndef SNOW_PME_WINDOW_H
#define SNOW_PME_WINDOW_H 1
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <string>

namespace SnowPME::Graphics {
	class Window {
	private:
		GLFWwindow* window = nullptr;
		std::string openGlVersion;
	public:
		Window(int height, int width, std::string title);
		void SwapBuffers();
		double GetTime();
		void PollEvents();
		bool IsMinimized();
		bool ShouldClose();
		~Window();
	};
}

#endif