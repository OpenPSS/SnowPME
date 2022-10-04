#include <Graphics/Window.hpp>
#include <Debug/Logger.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace SnowPME::Debug;

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
			Logger::Error("Failed to initalize GLES2.");
			throw new std::exception("Failed to initalize GLES2.");
		}
		this->openGlVersion = std::string((char*)glGetString(GL_VERSION));
		Logger::Info("GLES2 Version: "+this->openGlVersion);
	}
	Window::~Window() {
		glfwTerminate();
	}
}