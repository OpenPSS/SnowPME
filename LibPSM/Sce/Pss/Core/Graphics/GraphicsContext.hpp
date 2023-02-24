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
#include <Sce/Pss/Core/Errorable.hpp>

#include <LibSnowPME.hpp>
#include <mono/mono.h>

using namespace SnowPME::Util;
using namespace Sce::PlayStation::Core::Imaging;
using namespace Sce::PlayStation::Core::Graphics;

namespace Sce::Pss::Core::Graphics {
	class GraphicsContext : public GraphicsObject {
	private:
		ShaderProgram* currentShader = NULL;
		GraphicsObject* currentFrameBuffer = NULL;
		int numShaderUpdates = 0;

		int width = 0;
		int height = 0;
		PixelFormat colorFormat;
		PixelFormat depthFormat;
		MultiSampleMode multiSampleMode;
		GraphicsCapsState* capsState;


		std::string extensions;
		std::string renderer;
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
		Window* MainWindow();
		std::string Extensions();
		std::string Renderer();

		uint32_t BoundArrayBuffer();
		uint32_t BindArrayBuffer(uint32_t buffer);

		static GraphicsContext* GetGraphicsContext();
	};
}

#endif