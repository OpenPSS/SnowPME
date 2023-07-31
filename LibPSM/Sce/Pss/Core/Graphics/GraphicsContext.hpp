#ifndef LIB_PSS_GRAPHICSCONTEXT_H
#define LIB_PSS_GRAPHICSCONTEXT_H 1

#include <Sce/PlayStation/Core/Graphics/DrawMode.hpp>
#include <Sce/PlayStation/Core/Graphics/PixelFormat.hpp>
#include <Sce/PlayStation/Core/Graphics/GraphicsUpdate.hpp>
#include <Sce/PlayStation/Core/Graphics/ClearMask.hpp>
#include <Sce/PlayStation/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/PlayStation/Core/Graphics/GraphicsState.hpp>
#include <Sce/PlayStation/Core/Graphics/Primitive.hpp>
#include <Sce/PlayStation/Core/Graphics/GraphicsCapsState.hpp>
#include <Sce/PlayStation/Core/Graphics/MultiSampleMode.hpp>
#include <Sce/PlayStation/Core/Imaging/ImageSize.hpp>

#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/FrameBuffer.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/Texture.hpp>

#include <Sce/Pss/Core/Timing/DeltaTime.hpp>

#include <Sce/Pss/Core/Errorable.hpp>

#include <LibShared.hpp>
#include <mono/mono.h>
#include <glad/glad.h>

using namespace Sce::PlayStation::Core::Imaging;
using namespace Sce::PlayStation::Core::Graphics;
using namespace Sce::Pss::Core::Timing;

namespace Sce::Pss::Core::Graphics {
	
	class GraphicsContext : public GraphicsObject {
	private:
		const int shaderProgramHandleOffset = 0;
		const int frameBufferHandleOffset = 1;
		const int vertexBufferHandleOffset = 4;
		const int textureHandleOffset = 8;

		const int glStencilOps[8] = { GL_KEEP, GL_ZERO, GL_REPLACE, GL_INVERT, GL_INCR, GL_DECR, GL_INCR_WRAP, GL_DECR_WRAP };
		const int glDepthFuncs[8] = { GL_ALWAYS, GL_NEVER, GL_EQUAL, GL_NOTEQUAL, GL_LESS, GL_GREATER, GL_LEQUAL, GL_GEQUAL };
		const int glCullModes[4] = { GL_BACK, GL_FRONT, GL_BACK, GL_FRONT_AND_BACK };
		const int glCullFrontFaceModes[2] = { GL_CW, GL_CCW };
		const int glBlendModes[4] = { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD };
		
		const int glBlendSFactor[16] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
										GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
										GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE,
										GL_ZERO, GL_ZERO, GL_ZERO };

		const int glBlendDFactor[16] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
										GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
										GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ZERO, GL_ZERO,
										GL_ZERO, GL_ZERO, GL_ZERO };

		ShaderProgram* currentProgram = nullptr;
		FrameBuffer* currentFrameBuffer = nullptr;
		VertexBuffer* currentVertexBuffers[4];
		Texture* currentTextures[4];
		
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

		static GraphicsContext* GetGraphicsContext();
	};
}

#endif