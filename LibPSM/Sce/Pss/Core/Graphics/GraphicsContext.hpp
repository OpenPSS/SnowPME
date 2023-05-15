#ifndef LIB_PSM_GRAPHICSCONTEXT_H
#define LIB_PSM_GRAPHICSCONTEXT_H 1

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

#include <Sce/Pss/Core/Errorable.hpp>

#include <LibShared.hpp>
#include <mono/mono.h>

using namespace Sce::PlayStation::Core::Imaging;
using namespace Sce::PlayStation::Core::Graphics;

namespace Sce::Pss::Core::Graphics {
	class GraphicsContext : public GraphicsObject {
	private:
		ShaderProgram* currentProgram;
		FrameBuffer* currentFrameBuffer;
		VertexBuffer* currentVertexBuffer;
		Texture* currentTextureBuffer;

		int numShaderUpdates = 0;

		int width = 0;
		int height = 0;
		PixelFormat colorFormat;
		PixelFormat depthFormat;
		MultiSampleMode multiSampleMode;
		GraphicsCapsState* capsState;


		std::string extensions;
		std::string renderer;

		GraphicsUpdate updateNotifyFlag;

		int boundArrayBuffer;

	public:
		GraphicsContext(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode);
		~GraphicsContext();

		int Update(GraphicsUpdate update, GraphicsState* state, int* handles);
		int Width();
		int Height();
		PixelFormat ColorFormat();
		PixelFormat DepthFormat();
		MultiSampleMode MSampleMode();
		GraphicsCapsState* CapsState();
		std::string Extensions();
		std::string Renderer();

		// actual graphics handling ..
		GraphicsUpdate NotifyUpdate(GraphicsUpdate updateFlag);
		void CheckUpdate(GraphicsState* state);
		void UpdateHandles(GraphicsUpdate notifyFlag);
		void UpdateState(GraphicsUpdate notifyFlag, GraphicsState* state);
		void UpdateMultiScreen(GraphicsUpdate notifyFlag, GraphicsState* state, char unk); // TODO: work out this unknown parameter;

		static GraphicsContext* GetGraphicsContext();
	};
}

#endif