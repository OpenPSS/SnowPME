#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Sce::Pss::Core::Graphics {
	void OpenGL::SetShaderProgram(ShaderProgram* shaderProgram) {
		OpenGL::activeShaderProgram = shaderProgram;
		if (shaderProgram == NULL) {
			glUseProgram(0);
		}
		else {
			int oglProgram = shaderProgram->Program();
			glUseProgram(oglProgram);
		}
	}

}