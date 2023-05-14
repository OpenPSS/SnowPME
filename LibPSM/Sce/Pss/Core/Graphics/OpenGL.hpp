#ifndef LIB_PSM_OPENGL
#define LIB_PSM_OPENGL 1

#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>

namespace Sce::Pss::Core::Graphics {

	class OpenGL {
	private:
		static ShaderProgram* activeShaderProgram;
		static VertexBuffer* activeVertexBuffer;
	public:
		static void SetShaderProgram(ShaderProgram* shaderProgram);

	};

}

#endif