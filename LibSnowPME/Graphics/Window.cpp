#include <Graphics/Window.hpp>

#include <LibShared.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <LibPSM.hpp>

using namespace Shared::Debug;

namespace SnowPME::Graphics {

	Window::Window(int height, int width, std::string title) {
		if (!glfwInit()) {
			Logger::Error("Failed to initalize GLFW.");
			throw new std::exception("Failed to initalize GLFW.");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (this->window == NULL) {
			Logger::Error("Failed to create GLFW window.");
			throw new std::exception("Failed to create GLFW window.");
		}

		glfwMakeContextCurrent(this->window);

		if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
			Logger::Error("Failed to initalize GL.");
			throw new std::exception("Failed to initalize GL.");
		}

		int framebufferWidth = 0;
		int framebufferHeight = 0;
		glfwGetFramebufferSize(this->window, &framebufferWidth, &framebufferHeight);
		glViewport(0, 0, framebufferWidth, framebufferHeight);

		this->openGlVersion = std::string((char*)glGetString(GL_VERSION));
	}

	void Window::PollEvents() {
		glfwPollEvents();
	}
	double Window::GetTime() {
		return glfwGetTime();
	}

	bool Window::IsMinimized() {
		return glfwGetWindowAttrib(window, GLFW_ICONIFIED);
	}

	void Window::SwapBuffers() {
		glfwSwapBuffers(this->window);
	}
	
	bool Window::ShouldClose() {
		return glfwWindowShouldClose(this->window);
	}

	Window::~Window() {
		glfwTerminate();
	}

}