#ifndef LIB_PSM_OPENGL
#define LIB_PSM_OPENGL 1

#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/FrameBuffer.hpp>

namespace Sce::Pss::Core::Graphics {

	class OpenGL {
	private:
		static VertexBuffer* activeVertexBuffer;
		static FrameBuffer* activeFrameBuffer;
		static ShaderProgram* activeShaderProgram;
		static Texture* activeTexture;


	public:

		static void SetShaderProgram(ShaderProgram* shaderProgram);
		static void SetVertexBuffer(VertexBuffer* vertexBuffer);
		static void SetFrameBuffer(FrameBuffer* frameBuffer);
		static void SetTexture(Texture* texture);
	};

}

#endif