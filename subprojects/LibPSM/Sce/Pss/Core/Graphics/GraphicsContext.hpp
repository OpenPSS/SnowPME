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
#include <list>
#include <memory>
#include <cstdint>
#include <vector>

using namespace Sce::Pss::Core::Imaging;
using namespace Sce::Pss::Core::Timing;

namespace Sce::Pss::Core::Graphics {

	
	class GraphicsContext : public PsmObject<GraphicsContext>, public PsmUniqueObject<GraphicsContext> {
	private:
		const int shaderProgramHandleOffset = 0;
		const int frameBufferHandleOffset = 1;
		const int vertexBufferHandleOffset = 4;
		const int textureHandleOffset = 8;

		static const GLenum glEnableModes[0x7];
		static const GLenum glStencilOps[0x8];
		static const GLenum glDepthFuncs[0x8];
		static const GLenum glBlendModes[0x4];
		static const GLenum glBlendSFactor[0x10];
		static const GLenum glBlendDFactor[0x10];
		static const GLenum glCullModes[0x4];
		static const GLenum glCullFrontFaceModes[0x2];

		ShaderProgram* currentProgram = nullptr;
		FrameBuffer* currentFrameBuffer = nullptr;
		
		std::vector<VertexBuffer*> vertexBuffers;
		std::vector<Texture*> textures;
		EnableMode currentEnableModes = EnableMode::None;

		int cullFaceBits = 0;

		short frameCount = 0;
		int numScreens = 0;
		bool hasFrameBuffer = true;
		bool hasShaderOrNoFrameBuffer = false;
		bool frameInProgress = false;

		GraphicsUpdate updateNotifyFlag = GraphicsUpdate::None;
		GraphicsUpdate updateNotifyDataFlag = GraphicsUpdate::None;

		std::unique_ptr<DeltaTime> minFrameDelta = nullptr;

		int setCurrentObject(ShaderProgram* program);
		int setCurrentObject(FrameBuffer* frameBuffer);


		static GraphicsCapsState capsState;

	public:
		GraphicsContext(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode);
		~GraphicsContext() = default;
		int ActiveStateChanged(bool state);
		
		int EndFrame();
		int BeginFrame();

		int Update(GraphicsUpdate update, GraphicsState* state, int* handles);
		int Clear(ClearMask mask);
		int SwapBuffers();

		int Width = Shared::Config::ScreenWidth(0);
		int Height = Shared::Config::ScreenHeight(0);

		PixelFormat ColorFormat = PixelFormat::None;
		PixelFormat DepthFormat = PixelFormat::None;
		MultiSampleMode SampleMode = MultiSampleMode::None;

		std::string Extensions = "";
		std::string Renderer = "";

		// actual graphics handling ..
		GraphicsUpdate NotifyUpdate(GraphicsUpdate updateFlag);
		GraphicsUpdate NotifyUpdateData(GraphicsUpdate updateDataFlag);

		static GraphicsCapsState& GetCaps();

		int CheckUpdate(GraphicsState* state);
		int UpdateHandles(GraphicsUpdate notifyFlag);
		int UpdateState(GraphicsUpdate notifyFlag, GraphicsState* state);
		int UpdateMultiScreen(GraphicsUpdate notifyFlag, GraphicsState* state, char unk); // TODO: work out this unknown parameter;
	};
}

#endif