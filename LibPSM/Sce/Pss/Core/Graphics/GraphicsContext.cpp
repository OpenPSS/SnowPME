#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Handles.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>

#include <Sce/PlayStation/Core/Graphics/GraphicsExtension.hpp>

#include <glad/glad.h>
#include <LibShared.hpp>

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;

using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {
	static GraphicsContext* activeGraphicsContext = NULL;

	GraphicsContext* GraphicsContext::GetGraphicsContext() {
		return activeGraphicsContext;
	}

	int GraphicsContext::Height() {
		return this->height;
	}

	int GraphicsContext::Width() {
		return this->width;
	}

	PixelFormat GraphicsContext::ColorFormat() {
		return this->colorFormat;
	}
	PixelFormat GraphicsContext::DepthFormat() {
		return this->depthFormat;
	}
	MultiSampleMode GraphicsContext::MSampleMode() {
		return this->multiSampleMode;
	}
	GraphicsCapsState* GraphicsContext::CapsState() {
		return this->capsState;
	}

	int GraphicsContext::Update(GraphicsUpdate update, GraphicsState* state, int* handles) {


		//check if update is not VertexBuffer, Texture, VertexBuffer0, VertexBufferN, Texture0, or TextureN
		GraphicsUpdate gupdate = update;
		if ((update & 0xFFFF0000) != GraphicsUpdate::None)
		{

			if ((update & GraphicsUpdate::ShaderProgram) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::ShaderProgram");
				ShaderProgram* graphObj = (ShaderProgram*)Handles::GetHandle(handles[0]);
				if (graphObj != this->currentProgram) {
					if (this->currentProgram != NULL) {
						GraphicsObject::Release(this->currentProgram);
					}

					this->currentProgram = graphObj;

					if (graphObj != NULL) {
						graphObj->Update = true;
					}
				}
			}
			if ((update & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::FrameBuffer");
				if (Handles::IsValid(handles[1])) {
					FrameBuffer* graphObj = (FrameBuffer*)Handles::GetHandle(handles[1]);
					if (graphObj != this->currentFrameBuffer) {
						if (this->currentFrameBuffer != NULL) {
							GraphicsObject::Release(this->currentFrameBuffer);
						}

						this->currentFrameBuffer = graphObj;

						if (graphObj != NULL) {
							graphObj->Update = true;
						}
					}
				}
				else {
					if (this->currentFrameBuffer != NULL) {
						GraphicsObject::Release(this->currentFrameBuffer);
					}
					this->currentFrameBuffer = NULL;
				}
			}
			if ((update & (GraphicsUpdate::VertexBuffer0 | GraphicsUpdate::VertexBufferN)) == GraphicsUpdate::None)
			{
				Logger::Debug("update & (GraphicsUpdate::VertexBuffer0 | GraphicsUpdate::VertexBufferN)");

				if ((update & (GraphicsUpdate::Texture | GraphicsUpdate::TextureN)) != GraphicsUpdate::None) {

					if (((update & (GraphicsUpdate::TextureN)) == GraphicsUpdate::None)) {
						update = (update | GraphicsUpdate::Enable);
					}

					if (((update & (GraphicsUpdate::TextureN)) != GraphicsUpdate::None)) {
						update = (update | GraphicsUpdate::DepthRange);
					}

				}

			}

			int flg = ((update & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) ? 4 : 1;

			Logger::Error("GraphicsUpdate::VertexBuffer. is not fully implemented yet.");
		}

		this->NotifyUpdate(gupdate);
		this->CheckUpdate(state);
		return PSM_ERROR_NO_ERROR;
	}

	void GraphicsContext::UpdateHandles(GraphicsUpdate notifyFlag) {
		Logger::Debug(__FUNCTION__);

		if ((notifyFlag & GraphicsUpdate::ShaderProgram) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::ShaderProgram");
			ShaderProgram* curProgram = this->currentProgram;
			OpenGL::SetShaderProgram(curProgram);
			
			if (curProgram != NULL)
				curProgram->Update = false;

			notifyFlag = notifyFlag | GraphicsUpdate::VertexBuffer;
		}
		if ((notifyFlag & GraphicsUpdate::VertexBuffer) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::VertexBuffer");
			//VertexBuffer* curVertex = this->currentVertex;

			Logger::Error("GraphicsUpdate::VertexBuffer is not fully implemented yet.");
		}
		if ((notifyFlag & GraphicsUpdate::Texture) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::Texture");
			Logger::Error("GraphicsUpdate::Texture is not fully implemented yet.");
		}
		if ((notifyFlag & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::FrameBuffer");
			FrameBuffer* curFrameBuffer = this->currentFrameBuffer;
			OpenGL::SetFrameBuffer(curFrameBuffer);

			if(curFrameBuffer != NULL)
				curFrameBuffer->Update = false;
		}

	}

	void GraphicsContext::UpdateState(GraphicsUpdate notifyFlag, GraphicsState* state) {
		Logger::Debug(__FUNCTION__);
	}

	void GraphicsContext::UpdateMultiScreen(GraphicsUpdate notifyFlag, GraphicsState* state, char unk) {
		Logger::Debug(__FUNCTION__);
	}


	void GraphicsContext::CheckUpdate(GraphicsState* state) {
		GraphicsUpdate notifyFlag = this->updateNotifyFlag;
		if (this->updateNotifyFlag != GraphicsUpdate::None) {
			this->updateNotifyFlag = GraphicsUpdate::None;

			if ((notifyFlag & 0xFFFF0000) != GraphicsUpdate::None)
				this->UpdateHandles(notifyFlag);
			
			if (notifyFlag != GraphicsUpdate::None)
				this->UpdateState(notifyFlag, state);

			if (Shared::Config::ScreenTotal() >= 2)
				this->UpdateMultiScreen(notifyFlag, state, 0);
		}
	}

	GraphicsUpdate GraphicsContext::NotifyUpdate(GraphicsUpdate updateFlag) {
		this->updateNotifyFlag = this->updateNotifyFlag | updateFlag;
		return updateFlag;
	}

	std::string GraphicsContext::Extensions() {
		return this->extensions;
	}
	std::string GraphicsContext::Renderer() {
		return this->renderer;
	}

	GraphicsContext::~GraphicsContext() {
		delete this->capsState;
		activeGraphicsContext = NULL;
	}

	GraphicsContext::GraphicsContext(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode) {
		if (this->GetGraphicsContext() != NULL) 
		{ 
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return;
		}
		if (Thread::IsMainThread()) {
			this->width = width;
			this->height = height;
			this->colorFormat = colorFormat;
			this->depthFormat = depthFormat;
			this->multiSampleMode = multiSampleMode;
			this->capsState = new GraphicsCapsState();

			// Set width/height
			if (width == 0)
				this->width = Shared::Config::ScreenWidth(0);
			if (height == 0)
				this->height = Shared::Config::ScreenHeight(0);

			// set depth formats and stuff
			int redBits = 0;
			int greenBits = 0;
			int blueBits = 0;
			int alphaBits = 0;
			int depthBits = 0;
			int stencilBits = 0;
			int glSamples = 0;

			glGetIntegerv(GL_RED_BITS, &redBits);
			glGetIntegerv(GL_GREEN_BITS, &greenBits);
			glGetIntegerv(GL_BLUE_BITS, &blueBits);
			glGetIntegerv(GL_ALPHA_BITS, &alphaBits);
			glGetIntegerv(GL_DEPTH_BITS, &depthBits);
			glGetIntegerv(GL_STENCIL_BITS, &stencilBits);
			glGetIntegerv(GL_SAMPLES, &glSamples);

			if (depthFormat == PixelFormat::None) {
				this->depthFormat = PixelFormat::None;

				if (depthBits >= 16)
					this->depthFormat = (stencilBits >= 8) ? PixelFormat::Depth16Stencil8 : PixelFormat::Depth16;
				if (depthBits >= 24)
					this->depthFormat = (stencilBits >= 8) ? PixelFormat::Depth24Stencil8 : PixelFormat::Depth24;
			}

			if (colorFormat == PixelFormat::None) {
				this->colorFormat = PixelFormat::Rgb565;
				if (redBits >= 8 && greenBits >= 8 && blueBits >= 8 && alphaBits >= 8)
					this->colorFormat = PixelFormat::Rgba;
			}

			if (multiSampleMode == MultiSampleMode::None) {
				this->multiSampleMode = MultiSampleMode::None;
				if (glSamples >= 2)
					this->multiSampleMode = MultiSampleMode::Msaa2x;
				if (glSamples >= 4)
					this->multiSampleMode = MultiSampleMode::Msaa4x;
			}

			// Populate CapsState

			glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &this->capsState->MaxViewportWidth);
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &this->capsState->MaxTextureSize);
			glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &this->capsState->MaxCubeMapTextureSize);
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &this->capsState->MaxRenderbufferSize);
			glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &this->capsState->MaxVertexUniformVectors);
			glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &this->capsState->MaxFragmentUniformVectors);
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &this->capsState->MaxVertexAttribs);
			glGetIntegerv(GL_MAX_VARYING_VECTORS, &this->capsState->MaxVaryingVectors);
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &this->capsState->MaxCombinedTextureImageUnits);
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &this->capsState->MaxTextureImageUnits);
			glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &this->capsState->MaxVertexTextureImageUnits);

			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &this->capsState->MaxTextureMaxAnisotropy);
			glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, &this->capsState->MinAliasedLineWidth);
			glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, &this->capsState->MinAliasedPointSize);

			char* glExtensions = (char*)glGetString(GL_EXTENSIONS);

			if(glExtensions == NULL)
				this->extensions = std::string();
			else
				this->extensions = std::string(glExtensions);

			std::vector<std::string> extensionList = Shared::String::Util::Split(this->extensions, " ");

			Logger::Info("GL Vendor: " + std::string((char*)glGetString(GL_VENDOR)));
			Logger::Info("GL Renderer: " + std::string((char*)glGetString(GL_RENDERER)));
			Logger::Info("GL Version: " + std::string((char*)glGetString(GL_VERSION)));
			Logger::Info("GL Shader Language Version: " + std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));

			this->renderer = std::string((char*)glGetString(GL_RENDERER));

			unsigned int gext = GraphicsExtension::None;
			for (std::string extension : extensionList) {

				if (extension == "GL_OES_depth_texture")
					gext |= GraphicsExtension::DepthTexture;

				if (extension == "GL_OES_texture_3D")
					gext |= GraphicsExtension::Texture3D;

				if (extension == "GL_OES_texture_npot")
					gext |= GraphicsExtension::TextureNpot;

				if (extension == "GL_EXT_texture_filter_anisotropic")
					gext |= GraphicsExtension::TextureFilterAnisotropic;

				if (extension == "GL_OES_rgb8_rgba8")
					gext |= GraphicsExtension::Rgb8Rgba8;

				if (extension == "GL_OES_depth24")
					gext |= GraphicsExtension::Depth24;

				if (extension == "GL_OES_depth32")
					gext |= GraphicsExtension::Depth32;

				if (extension == "GL_OES_packed_depth_stencil")
					gext |= GraphicsExtension::PackedDepthStencil;

				if (extension == "GL_OES_vertex_half_float")
					gext |= GraphicsExtension::TextureHalfFloat;

				if (extension == "GL_OES_vertex_type_10_10_10_2")
					gext |= GraphicsExtension::Vertex1010102;

				if (extension == "GL_OES_texture_float")
					gext |= GraphicsExtension::TextureFloat;

				if (extension == "GL_OES_texture_float_linear")
					gext |= GraphicsExtension::TextureFloatLinear;

				if (extension == "GL_OES_texture_half_float_linear")
					gext |= GraphicsExtension::TextureHalfFloatLinear;

				if (extension == "GL_EXT_texture_type_2_10_10_10_REV")
					gext |= GraphicsExtension::Texture2101010Rev;

				if (extension == "GL_NV_texture_npot_2D_mipmap")
					gext |= GraphicsExtension::TextureNPot2DMipMap;

				if (extension == "GL_EXT_draw_instanced")
					gext |= GraphicsExtension::DrawInstanced;

				if (extension == "GL_EXT_instanced_arrays")
					gext |= GraphicsExtension::InstancedArrays;

			}
			if (this->capsState->MaxTextureSize > 0x800)
				this->capsState->MaxTextureSize = 0x800;
			if (this->capsState->MaxCubeMapTextureSize > 0x800)
				this->capsState->MaxCubeMapTextureSize = 0x800;
			if (this->capsState->MaxRenderbufferSize > 0x800)
				this->capsState->MaxRenderbufferSize = 0x800;
			if (this->capsState->MaxVertexUniformVectors > 0x80)
				this->capsState->MaxVertexUniformVectors = 0x80;
			if (this->capsState->MaxFragmentUniformVectors > 0x40)
				this->capsState->MaxFragmentUniformVectors = 0x40;
			if (this->capsState->MaxVertexAttribs > 0x8)
				this->capsState->MaxVertexAttribs = 0x8;
			if (this->capsState->MaxVaryingVectors > 0x8)
				this->capsState->MaxVaryingVectors = 0x8;
			if (this->capsState->MaxCombinedTextureImageUnits > 0x8)
				this->capsState->MaxCombinedTextureImageUnits = 0x8;
			if (this->capsState->MaxTextureImageUnits > 0x8)
				this->capsState->MaxTextureImageUnits = 0x8;
			if (this->capsState->MaxVertexTextureImageUnits > 0x0)
				this->capsState->MaxVertexTextureImageUnits = 0x0;

			if (this->capsState->MaxAliasedLineWidth > 8.0)
				this->capsState->MaxAliasedLineWidth = 8.0;
			if (this->capsState->MaxAliasedPointSize > 128.0)
				this->capsState->MaxAliasedPointSize = 128.0;

			this->capsState->Extension = (gext & 0x3A9B8);

			activeGraphicsContext = this;

			this->currentProgram = nullptr;
			this->currentFrameBuffer = nullptr;
			this->currentVertexBuffer = nullptr;
			this->currentTextureBuffer = nullptr;

		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
			this->SetError(PSM_ERROR_COMMON_INVALID_OPERATION);
		}
	}
}