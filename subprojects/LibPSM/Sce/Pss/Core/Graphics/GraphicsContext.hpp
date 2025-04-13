#ifndef LIB_PSS_GRAPHICSCONTEXT_H
#define LIB_PSS_GRAPHICSCONTEXT_H 1

#include <Sce/Pss/Core/Graphics/DrawMode.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsUpdate.hpp>
#include <Sce/Pss/Core/Graphics/ClearMask.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsState.hpp>
#include <Sce/Pss/Core/Graphics/Primitive.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsCapsState.hpp>
#include <Sce/Pss/Core/Graphics/MultiSampleMode.hpp>
#include <Sce/Pss/Core/Imaging/ImageSize.hpp>

#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/FrameBuffer.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/Timing/DeltaTime.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>

#include <LibShared.hpp>
#include <mono/mono.h>
#include <glad/glad.h>
using namespace Sce::Pss::Core::Imaging;
using namespace Sce::Pss::Core::Timing;

namespace Sce::Pss::Core::Graphics {

	
	class GraphicsContext : public GraphicsObject, public PsmUniqueObject<GraphicsContext> {
	private:
		const int shaderProgramHandleOffset = 0;
		const int frameBufferHandleOffset = 1;
		const int vertexBufferHandleOffset = 4;
		const int textureHandleOffset = 8;
		const GLenum glEnableModes[7] = { GL_SCISSOR_TEST, GL_CULL_FACE, GL_BLEND, GL_DEPTH_TEST,
										  GL_POLYGON_OFFSET_FILL, GL_STENCIL_TEST, GL_DITHER };
		const GLenum glStencilOps[8] = { GL_KEEP, GL_ZERO, GL_REPLACE, GL_INVERT,
									  GL_INCR, GL_DECR, GL_INCR_WRAP, GL_DECR_WRAP };
		const GLenum glDepthFuncs[8] = { GL_ALWAYS, GL_NEVER, GL_EQUAL, GL_NOTEQUAL, GL_LESS,
									  GL_GREATER, GL_LEQUAL, GL_GEQUAL };
		const GLenum glBlendModes[4] = { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD };
		
		const GLenum glBlendSFactor[16] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
										GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
										GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE,
										GL_ZERO, GL_ZERO, GL_ZERO };

		const GLenum glBlendDFactor[16] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
										GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
										GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ZERO, GL_ZERO,
										GL_ZERO, GL_ZERO, GL_ZERO };
		const GLenum glCullModes[4] = { GL_BACK, GL_FRONT, GL_BACK, GL_FRONT_AND_BACK };
		const GLenum glCullFrontFaceModes[2] = { GL_CW, GL_CCW };

		ShaderProgram* currentProgram = nullptr;
		FrameBuffer* currentFrameBuffer = nullptr;
		VertexBuffer* currentVertexBuffers[4];
		Texture* currentTextures[4];
		EnableMode currentEnableModes = EnableMode::None;

		int cullFaceBits = 0;

		short frameCount = 0;
		int numScreens = 0;
		bool hasFrameBuffer = false;
		bool hasShaderOrNoFrameBuffer = false;
		bool frameInProgress = false;

		GraphicsUpdate updateNotifyFlag = GraphicsUpdate::None;
		GraphicsUpdate updateNotifyDataFlag = GraphicsUpdate::None;

		DeltaTime* minFrameDelta = nullptr;


		int setCurrentObject(ShaderProgram* program);
		int setCurrentObject(FrameBuffer* frameBuffer);

		static void ErrorCallback(
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam
		);

	public:
		GraphicsContext(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode);
		~GraphicsContext();
		int ActiveStateChanged(bool state);
		
		int EndFrame();
		int BeginFrame();

		int Update(GraphicsUpdate update, GraphicsState* state, int* handles);
		int Clear(ClearMask mask);
		int SwapBuffers();

		int Width = 960;
		int Height = 544;

		PixelFormat ColorFormat;
		PixelFormat DepthFormat;
		MultiSampleMode SampleMode;
		GraphicsCapsState* CapsState;

		std::string Extensions = "";
		std::string Renderer = "";

		// actual graphics handling ..
		GraphicsUpdate NotifyUpdate(GraphicsUpdate updateFlag);
		GraphicsUpdate NotifyUpdateData(GraphicsUpdate updateDataFlag);


		void CheckUpdate(GraphicsState* state);
		void UpdateHandles(GraphicsUpdate notifyFlag);
		void UpdateState(GraphicsUpdate notifyFlag, GraphicsState* state);
		void UpdateMultiScreen(GraphicsUpdate notifyFlag, GraphicsState* state, char unk); // TODO: work out this unknown parameter;
	};
}

#endif