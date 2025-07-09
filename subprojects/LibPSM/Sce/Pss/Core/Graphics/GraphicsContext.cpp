#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsExtension.hpp>
#include <Sce/Pss/Core/Graphics/ColorMask.hpp>

#include <LibShared.hpp>
#include <glad/glad.h>
#include <string.h>
#include <math.h>

using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::System;
using namespace Shared::Debug;
using namespace Shared::Windowing;

namespace Sce::Pss::Core::Graphics {

	int GraphicsContext::ActiveStateChanged(bool state) {
		UNIMPLEMENTED();
	}

	int GraphicsContext::setCurrentObject(std::shared_ptr<ShaderProgram> shaderProgram) {
		int result = PSM_ERROR_NO_ERROR;

		if (shaderProgram != this->currentProgram) {
			// check if the current program is set 
			if (this->currentProgram != nullptr) {
				// get and clear the update flag
				bool activeFlag = this->currentProgram->Active;
				// clear the active flag
				this->currentProgram->Active = false;
				if (activeFlag) { // if the update flag was set, call the active state changed.
					result = this->currentProgram->ActiveStateChanged(true);
				}
			}

			// update the current program
			this->currentProgram = shaderProgram;
			if (shaderProgram != nullptr) {
				shaderProgram->Active = true;
			}

		}

		return result;
	}
	int GraphicsContext::setCurrentObject(std::shared_ptr<FrameBuffer> frameBuffer) {
		int result = PSM_ERROR_NO_ERROR;

		if (frameBuffer != this->currentFrameBuffer) {
			// check if the current frame buffer is set 
			if (this->currentFrameBuffer != nullptr) {
				// get and clear the update flag
				bool activeFlag = this->currentFrameBuffer->Active;
				// clear the active flag
				this->currentFrameBuffer->Active = false;
				if (activeFlag) { // if the update flag was set, call the active state changed.
					result = this->currentFrameBuffer->ActiveStateChanged(true);
				}
			}

			// update the current frame buffer
			this->currentFrameBuffer = frameBuffer;
			if (frameBuffer != nullptr) {
				frameBuffer->Active = true;
			}

		}

		return result;
	}
	
	int GraphicsContext::Update(GraphicsUpdate update, GraphicsState* state, int* handles) {


		//check if update is not VertexBuffer, Texture, VertexBuffer0, VertexBufferN, Texture0, or TextureN

		if ((update & 0xFFFF0000) != GraphicsUpdate::None)
		{
			// check update is a ShaderProgram
			if ((update & GraphicsUpdate::ShaderProgram) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::ShaderProgram");

				// Resolve the handle for the new shader program
				std::shared_ptr<ShaderProgram> workingShaderProgram = Handles<ShaderProgram>::Get(handles[GraphicsContext::shaderProgramHandleOffset]);
				
				// Set this shader program as the currently active shader program.
				setCurrentObject(workingShaderProgram);
			}

			// check update is a FrameBuffer
			if ((update & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::FrameBuffer");

				int fbHandle = handles[GraphicsContext::frameBufferHandleOffset];
				// Check this handle is valid ..
				if (Handles<FrameBuffer>::IsValid(fbHandle)) {
					// Resolve the handle for the new shader program
					std::shared_ptr<FrameBuffer> workingFrameBuffer = Handles<FrameBuffer>::Get(fbHandle);

					// Set this frame buffer as the currently active frame buffer.
					setCurrentObject(workingFrameBuffer);
				}
				else {
					// Check the current frame buffer is set
					if (this->currentFrameBuffer != nullptr) {
						// get the active flag
						bool activeFlag = this->currentFrameBuffer->Active;
						// clear the active flag
						this->currentFrameBuffer->Active = false;
						// if the flag was set, call ActiveStateChanged
						if (activeFlag) {
							this->currentFrameBuffer->ActiveStateChanged(true);
						}

						// unset the current framebuffer.
						this->currentFrameBuffer = nullptr;
					}
				}
			}

			// check update is GraphicsUpdate::VertexBuffer
			if ((update & GraphicsUpdate::VertexBuffer) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::VertexBuffer");
				int count = ((update & GraphicsUpdate::VertexBufferN) != GraphicsUpdate::None) ? 4 : 1;
				for (int i = 0; i < count; i++) {
					std::shared_ptr<VertexBuffer> workingVertexBuffer = Handles<VertexBuffer>::Get(handles[GraphicsContext::vertexBufferHandleOffset + i]);
					std::shared_ptr<VertexBuffer> currentVertexBuffer = this->vertexBuffers[i];

					if (currentVertexBuffer == workingVertexBuffer) {
						if (workingVertexBuffer != nullptr && workingVertexBuffer->unk21) {
							this->NotifyUpdateData(GraphicsUpdate::VertexBuffer);
						}
					}
					else {
						if (currentVertexBuffer != nullptr) {
							bool activeFlg = currentVertexBuffer->Active;
							currentVertexBuffer->Active = false;
							if (activeFlg) {
								currentVertexBuffer->ActiveStateChanged(true);
							}
						}

						this->vertexBuffers[i] = workingVertexBuffer;

						if (workingVertexBuffer != nullptr) {
							workingVertexBuffer->Active = true;
							if (workingVertexBuffer->unk21) {
								this->NotifyUpdateData(GraphicsUpdate::VertexBuffer);
							}
						}
					}
				}
			}
		
			// check update is GraphicsUpdate::Texture
			if ((update & GraphicsUpdate::Texture) != GraphicsUpdate::None)
			{
				Logger::Debug("update & GraphicsUpdate::Texture");
				int count = ((update < GraphicsUpdate::None) ? 8 : 1);
				UNIMPLEMENTED_MSG("update & GraphicsUpdate::Texture is not implemented");
			}

		}

		this->NotifyUpdate(update);
		this->CheckUpdate(state);
		return PSM_ERROR_NO_ERROR;
	}

	void GraphicsContext::UpdateHandles(GraphicsUpdate notifyFlag) {
		// check notifyFlag is ShaderProgram .
		if ((notifyFlag & GraphicsUpdate::ShaderProgram) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::ShaderProgram");

			// bind the current program in openGL
			OpenGL::SetShaderProgram(this->currentProgram.get());

			// set the vertexBuffer notify flag.
			notifyFlag = notifyFlag | GraphicsUpdate::VertexBuffer;
		}

		// check notifyFlag is VertexBuffer
		if ((notifyFlag & GraphicsUpdate::VertexBuffer) != GraphicsUpdate::None) {
			std::shared_ptr<ShaderProgram> program = this->currentProgram;
			
			int numAttributes = 0;
			if (program != nullptr) {
				int numAttributes = program->Attributes.size();
			}

			std::shared_ptr<VertexBuffer> vertexBuffer = this->vertexBuffers[0];

			int numStreams = 0;
			if (vertexBuffer != nullptr) {
				numStreams = vertexBuffer->NumStreams;
			}

			// TODO: what are these?
			int unk1 = 0xFFFF;
			int unk2 = 0xFFFF;

			OpenGL::SetVertexBuffer(vertexBuffer.get());

			if (numAttributes > 0) {

				for (int i = 0; i < numAttributes; i++) {
					int stream = program->GetAttributeStream(i);
					if (stream >= 0) {
						if (stream >= numStreams) {

							// TODO: this is actually while(1) strId++ 
							// if strId is >= 4, then it does a goto,
							// perhaps something like do while, and an if statement?
							// REF: sce::pss::core::graphics::GraphicsContext::UpdateHandles (psm.exe)

							for (int strId = 0; strId < 4; strId++) {
								vertexBuffer = this->vertexBuffers[i];
								
								if (vertexBuffer != nullptr) {
									numStreams = vertexBuffer->NumStreams;
									if (stream < numStreams) {
										if (strId > 0) numStreams = 0;
										OpenGL::SetVertexBuffer(vertexBuffer.get());
										break;
									}
								}

							}
						}
					}
				}
			}


			UNIMPLEMENTED_ERRORABLE("notifyFlag & GraphicsUpdate::VertexBuffer");
		}

		// check notifyFlag is Texture
		if ((notifyFlag & GraphicsUpdate::Texture) != GraphicsUpdate::None) {
			UNIMPLEMENTED_ERRORABLE("notifyFlag & GraphicsUpdate::Texture");
		}

		// check notifyFlag is FrameBuffer
		if ((notifyFlag & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::FrameBuffer");

			// bind the framebuffer
			OpenGL::SetFrameBuffer(this->currentFrameBuffer.get());
			
			// set hasNoFrameBuffer and HasShaderOrNoFrameBuffer flags
			this->hasFrameBuffer = (!this->currentFrameBuffer  || this->currentFrameBuffer->unk12 );
			this->hasShaderOrNoFrameBuffer = (this->currentProgram == nullptr && this->hasFrameBuffer);
		}
	}

	int GraphicsContext::Clear(ClearMask mask) {
		if (this->hasFrameBuffer) {
			int glMask = 0;
			if ((mask & ClearMask::Color) != ClearMask::None)
				glMask |= GL_COLOR_BUFFER_BIT;
			if ((mask & ClearMask::Depth) != ClearMask::None)
				glMask |= GL_DEPTH_BUFFER_BIT;
			if ((mask & ClearMask::Stencil) != ClearMask::None)
				glMask |= GL_STENCIL_BUFFER_BIT;

			glClear(glMask);
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Frame buffer is not available\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	
	int GraphicsContext::EndFrame() {
		WindowControl::EndFrame();

		if (Thread::IsMainThread() /* && !endframe_related_ns && endframe_related_0 && endframe_related */) {
			if (this->frameInProgress) {
				this->frameInProgress = false;
			}
			return PSM_ERROR_NO_ERROR;
		}
		else {
			return PSM_ERROR_ERROR;
		}
	}

	int GraphicsContext::BeginFrame() {
		WindowControl::StartFrame();

		if (Thread::IsMainThread() /* || endframe_related_ns || startframe_related || !endframe_related_0 || !endframe_related */) {
			if (this->frameInProgress) {
				this->frameInProgress = false;
			}
		}
		else {
			return PSM_ERROR_ERROR;
		}
		return PSM_ERROR_NO_ERROR;
	}

	int GraphicsContext::SwapBuffers() {
		
		// end the current frame ..
		this->EndFrame();

		// swap buffers ..
		glFlush();
		WindowControl::SwapBuffers();

		// begin a new frame
		this->BeginFrame();
		
		// increment the frame counter
		this->frameCount++;

		if (this->numScreens >= 2) {
			glDisable(GL_SCISSOR_TEST);
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);
			glEnable(GL_SCISSOR_TEST);
			this->NotifyUpdate(GraphicsUpdate::ClearColor | GraphicsUpdate::Scissor | GraphicsUpdate::Enable);
			// this->mscreen_something |= 1;
		}

		double deltaTime = static_cast<double>(minFrameDelta->CalculateDelta());
		if (deltaTime < minFrameDelta->MinDelta()) {
			double maxSleepTime = (1 / 16);
			deltaTime -= maxSleepTime;
			Thread::Sleep(deltaTime);
			minFrameDelta->CalculateDelta();
		}

		return PSM_ERROR_NO_ERROR;
	}

	void GraphicsContext::UpdateState(GraphicsUpdate notifyFlag, GraphicsState* state) {
		// check notify flag is Scissor, Viewport, Depthrange, ClearColor, ClearDepth, or ClearStencil
		if ((notifyFlag & 
			(GraphicsUpdate::Scissor |
			GraphicsUpdate::Viewport |
			GraphicsUpdate::DepthRange |
			GraphicsUpdate::ClearColor |
			GraphicsUpdate::ClearDepth |
			GraphicsUpdate::ClearStencil)) != GraphicsUpdate::None) {

			if ((notifyFlag & GraphicsUpdate::Scissor) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::Scissor");
				glScissor(state->scissor.X, state->scissor.Y, state->scissor.Width, state->scissor.Y);
			}

			if ((notifyFlag & GraphicsUpdate::Viewport) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::Viewport");

				// Set OpenGL viewport,
				// if the width or height is less than 0, then the height/width is set to 0.

				glViewport(
					state->viewport.X,
					state->viewport.Y,
					state->viewport.Width < 0 ? 0 : state->viewport.Width,
					state->viewport.Height < 0 ? 0 : state->viewport.Height);


			}

			if ((notifyFlag & GraphicsUpdate::DepthRange) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::DepthRange");
				// Set OpenGL Depth Range
				
				glDepthRangef(state->depthRange.X, state->depthRange.Y);

			}

			if ((notifyFlag & GraphicsUpdate::ClearColor) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ClearColor");
				// Set OpenGL Clear Color

				glClearColor(state->clearColor.X, state->clearColor.Y, state->clearColor.Z, state->clearColor.W);
			}

			if ((notifyFlag & GraphicsUpdate::ClearDepth) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ClearDepth");
				// Set OpenGL Clear Depth

				glClearDepthf(state->clearDepth);
			}

			if ((notifyFlag & GraphicsUpdate::ClearStencil) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ClearStencil");
				// Set OpenGL Clear Stencil

				glClearStencil(state->clearStencil);
			}

		}
			
		if ((notifyFlag & 0xE000) != GraphicsUpdate::None) { // TODO: work out what 0xE000 is.
			if ((notifyFlag & GraphicsUpdate::ColorMask) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ColorMask");

				using namespace Sce::Pss::Core::Graphics;

				glColorMask(
					(state->colorMask & ColorMask::R) != Sce::Pss::Core::Graphics::ColorMask::None,
					(state->colorMask & ColorMask::G) != Sce::Pss::Core::Graphics::ColorMask::None,
					(state->colorMask & ColorMask::B) != Sce::Pss::Core::Graphics::ColorMask::None,
					(state->colorMask & ColorMask::A) != Sce::Pss::Core::Graphics::ColorMask::None);

			}

			if ((notifyFlag & GraphicsUpdate::LineWidth) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::LineWidth");

				float lnAdd = state->lineWidth + 0.5f;
				float lnFloor = floor(lnAdd);
				float lnBase = 1.0f;
				if (lnFloor >= 1.0f)
				{
					lnBase = lnFloor;
					if (lnFloor > 8.0f)
						lnBase = 8.0f;
				}
				glLineWidth(lnBase);
			}
		}
		
		if ((notifyFlag & (
			GraphicsUpdate::CullFace |
			GraphicsUpdate::BlendFunc |
			GraphicsUpdate::DepthFunc |
			GraphicsUpdate::PolygonOffset |
			GraphicsUpdate::StencilFunc |
			GraphicsUpdate::StencilOp)) != GraphicsUpdate::None) {


			if ((notifyFlag & GraphicsUpdate::CullFace) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::CullFace");
				glCullFace(this->glCullModes[state->cullFace.bits & 3]);
				glFrontFace(this->glCullFrontFaceModes[(state->cullFace.bits >> 8) & 1]);

				if (state->cullFace.bits & 0xFF)
					this->cullFaceBits |=  2;
				else
					this->cullFaceBits |= 0xFFFFFFFD;
			}

			if ((notifyFlag & GraphicsUpdate::BlendFunc) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::BlendFunc");
				glBlendEquationSeparate(
					this->glBlendModes[state->blendFuncRgb.bits & 3],
					this->glBlendModes[state->blendFuncAlpha.bits & 3]);
				glBlendFuncSeparate(
					this->glBlendSFactor[(state->blendFuncRgb.bits >> 8) & 0xF],
					this->glBlendDFactor[(state->blendFuncRgb.bits & 0x0000FFFF) & 0xF],
					this->glBlendSFactor[(state->blendFuncAlpha.bits >> 8) & 0xF],
					this->glBlendDFactor[(state->blendFuncAlpha.bits & 0x0000FFFF) & 0xF]);
			}

			if ((notifyFlag & GraphicsUpdate::DepthFunc) != GraphicsUpdate::None)
			{
				Logger::Debug("notifyFlag & GraphicsUpdate::DepthFunc");
				glDepthFunc(glDepthFuncs[state->depthFunc.bits & 7]);
				glDepthMask((state->depthFunc.bits >> 8) & 0xFF);
			}
			if ((notifyFlag & GraphicsUpdate::PolygonOffset) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::PolygonOffset");
				glPolygonOffset(state->polygonOffset.Factor, state->polygonOffset.Units);
			}
			if ((notifyFlag & GraphicsUpdate::StencilFunc) != GraphicsUpdate::None)
			{
				Logger::Debug("notifyFlag & GraphicsUpdate::StencilFunc");
				
				glStencilFuncSeparate(GL_FRONT, 
									glDepthFuncs[state->stencilFuncFront.bits & 7],
									(state->stencilFuncFront.bits >> 8) & 0xFF,
									(state->stencilFuncFront.bits >> 16) & 0xFF
				);

				glStencilFuncSeparate(GL_BACK,
									glDepthFuncs[state->stencilFuncBack.bits & 7],
									(state->stencilFuncBack.bits >> 8) & 0xFF,
									(state->stencilFuncBack.bits >> 16) & 0xFF
				);

				glStencilMaskSeparate(GL_FRONT, (state->stencilFuncFront.bits >> 24) & 0xFF);
				glStencilMaskSeparate(GL_BACK, (state->stencilFuncBack.bits >> 24) & 0xFF);

			}
			if ((notifyFlag & GraphicsUpdate::StencilOp) != GraphicsUpdate::None)
			{
				Logger::Debug("notifyFlag & GraphicsUpdate::StencilOp");

				glStencilOpSeparate(
					GL_FRONT,
					glStencilOps[state->stencilOpFront.bits & 7],
					glStencilOps[(state->stencilOpFront.bits >> 8) & 7],
					glStencilOps[((state->stencilOpFront.bits >> 16) & 0xFFFF) & 7]
				);
				glStencilOpSeparate(
					GL_BACK,
					glStencilOps[state->stencilOpBack.bits & 7],
					glStencilOps[(state->stencilOpBack.bits >> 8) & 7],
					glStencilOps[((state->stencilOpBack.bits >> 16) & 0xFFFF) & 7]
				);
			}

		}

		if ((notifyFlag & GraphicsUpdate::Enable) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::Enable");
			EnableMode enableModeToggleFlags = (state->enable & this->cullFaceBits);
			EnableMode enableModeBitlist = (enableModeToggleFlags ^ this->currentEnableModes) & EnableMode::All;
			
			if (this->currentEnableModes == static_cast<EnableMode>(0xFF)) {
				enableModeBitlist = EnableMode::All;
			}

			this->currentEnableModes = enableModeToggleFlags;
			

			for (int i = 0; enableModeBitlist != EnableMode::None; i++) {
				// if there is an enable mode set
				if ((enableModeBitlist & 1) != EnableMode::None) {
					// check if should be enabled or disabled
					if ((enableModeToggleFlags & 1) != EnableMode::None) {
						glEnable(this->glEnableModes[i]);
					}
					else {
						glDisable(this->glEnableModes[i]);
					}
				}

				enableModeToggleFlags = enableModeToggleFlags >> 1;
				enableModeBitlist = enableModeBitlist >> 1;
			};
		}
	}

	int GraphicsContext::UpdateMultiScreen(GraphicsUpdate notifyFlag, GraphicsState* state, char unk) {
		UNIMPLEMENTED();
	}


	void GraphicsContext::CheckUpdate(GraphicsState* state) {
		GraphicsUpdate notifyFlag = this->updateNotifyFlag;
		if (this->updateNotifyFlag != GraphicsUpdate::None) {
			this->updateNotifyFlag = GraphicsUpdate::None;

			if ((notifyFlag & 0xFFFF0000) != GraphicsUpdate::None)
				this->UpdateHandles(notifyFlag);
			
			if (notifyFlag != GraphicsUpdate::None)
				this->UpdateState(notifyFlag, state);

			if (this->numScreens >= 2)
				this->UpdateMultiScreen(notifyFlag, state, 0);
		}
	}

	GraphicsUpdate GraphicsContext::NotifyUpdateData(GraphicsUpdate updateDataFlag) {
		this->updateNotifyDataFlag = this->updateNotifyDataFlag | updateDataFlag;
		return updateNotifyDataFlag;
	}

	GraphicsUpdate GraphicsContext::NotifyUpdate(GraphicsUpdate updateFlag) {
		this->updateNotifyFlag = this->updateNotifyFlag | updateFlag;
		return updateFlag;
	}


	GraphicsContext::~GraphicsContext() {
		if(this->CapsState != nullptr)
			delete this->CapsState;
	}
	void GraphicsContext::ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		Logger::Error("[" + std::string((type == GL_DEBUG_TYPE_ERROR ? "OPENGL ERROR" : "")) + " type : " + std::to_string(type) + " severity : " + std::to_string(severity) + "] " + std::string(message));
	}

	GraphicsContext::GraphicsContext(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode) {

		if (Thread::IsMainThread()) {

			this->Width = width;
			this->Height = height;
			this->ColorFormat = colorFormat;
			this->DepthFormat = depthFormat;
			this->SampleMode = multiSampleMode;
			this->CapsState = new GraphicsCapsState();

			// Set width/height
			if (width == 0)
				this->Width = Shared::Config::ScreenWidth(0);
			if (height == 0)
				this->Height = Shared::Config::ScreenHeight(0);

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
				this->DepthFormat = PixelFormat::None;

				if (depthBits >= 16)
					this->DepthFormat = (stencilBits >= 8) ? PixelFormat::Depth16Stencil8 : PixelFormat::Depth16;
				if (depthBits >= 24)
					this->DepthFormat = (stencilBits >= 8) ? PixelFormat::Depth24Stencil8 : PixelFormat::Depth24;
			}

			if (colorFormat == PixelFormat::None) {
				this->ColorFormat = PixelFormat::Rgb565;
				if (redBits >= 8 && greenBits >= 8 && blueBits >= 8 && alphaBits >= 8)
					this->ColorFormat = PixelFormat::Rgba;
			}

			if (multiSampleMode == MultiSampleMode::None) {
				this->SampleMode = MultiSampleMode::None;
				if (glSamples >= 2)
					this->SampleMode = MultiSampleMode::Msaa2x;
				if (glSamples >= 4)
					this->SampleMode = MultiSampleMode::Msaa4x;
			}

			// Populate CapsState

			glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &this->CapsState->MaxViewportWidth);
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &this->CapsState->MaxTextureSize);
			glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &this->CapsState->MaxCubeMapTextureSize);
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &this->CapsState->MaxRenderbufferSize);
			glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &this->CapsState->MaxVertexUniformVectors);
			glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &this->CapsState->MaxFragmentUniformVectors);
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &this->CapsState->MaxVertexAttribs);
			glGetIntegerv(GL_MAX_VARYING_VECTORS, &this->CapsState->MaxVaryingVectors);
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &this->CapsState->MaxCombinedTextureImageUnits);
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &this->CapsState->MaxTextureImageUnits);
			glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &this->CapsState->MaxVertexTextureImageUnits);

			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &this->CapsState->MaxTextureMaxAnisotropy);
			glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, &this->CapsState->MinAliasedLineWidth);
			glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, &this->CapsState->MinAliasedPointSize);

			char* glExtensions = (char*)glGetString(GL_EXTENSIONS);

			if(glExtensions == NULL)
				this->Extensions = std::string();
			else
				this->Extensions = std::string(glExtensions);

			std::vector<std::string> extensionList = Shared::String::Format::Split(this->Extensions, " ");

			char* glVendor = (char*)glGetString(GL_VENDOR);
			char* glRenderer = (char*)glGetString(GL_RENDERER);
			char* glVersion = (char*)glGetString(GL_VERSION);
			char* glslVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

			Logger::Info("GL Vendor: " + std::string(glVendor));
			Logger::Info("GL Renderer: " + std::string(glRenderer));
			Logger::Info("GL Version: " + std::string(glVersion));
			Logger::Info("GL Shader Language Version: " + std::string(glslVersion));

			this->Renderer = std::string((char*)glGetString(GL_RENDERER));

			unsigned int gext = GraphicsExtension::None;
			for (const std::string& extension : extensionList) {

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
			if (this->CapsState->MaxTextureSize > 0x800)
				this->CapsState->MaxTextureSize = 0x800;
			if (this->CapsState->MaxCubeMapTextureSize > 0x800)
				this->CapsState->MaxCubeMapTextureSize = 0x800;
			if (this->CapsState->MaxRenderbufferSize > 0x800)
				this->CapsState->MaxRenderbufferSize = 0x800;
			if (this->CapsState->MaxVertexUniformVectors > 0x80)
				this->CapsState->MaxVertexUniformVectors = 0x80;
			if (this->CapsState->MaxFragmentUniformVectors > 0x40)
				this->CapsState->MaxFragmentUniformVectors = 0x40;
			if (this->CapsState->MaxVertexAttribs > 0x8)
				this->CapsState->MaxVertexAttribs = 0x8;
			if (this->CapsState->MaxVaryingVectors > 0x8)
				this->CapsState->MaxVaryingVectors = 0x8;
			if (this->CapsState->MaxCombinedTextureImageUnits > 0x8)
				this->CapsState->MaxCombinedTextureImageUnits = 0x8;
			if (this->CapsState->MaxTextureImageUnits > 0x8)
				this->CapsState->MaxTextureImageUnits = 0x8;
			if (this->CapsState->MaxVertexTextureImageUnits > 0x0)
				this->CapsState->MaxVertexTextureImageUnits = 0x0;

			if (this->CapsState->MaxAliasedLineWidth > 8.0)
				this->CapsState->MaxAliasedLineWidth = 8.0;
			if (this->CapsState->MaxAliasedPointSize > 128.0)
				this->CapsState->MaxAliasedPointSize = 128.0;

			this->CapsState->Extension = (gext & (GraphicsExtension::TextureFilterAnisotropic |
													GraphicsExtension::Rgb8Rgba8 | 
													GraphicsExtension::Depth24 | 
													GraphicsExtension::PackedDepthStencil | 
													GraphicsExtension::VertexHalfFloat | 
													GraphicsExtension::TextureHalfFloat | 
													GraphicsExtension::TextureHalfFloatLinear | 
													GraphicsExtension::TextureNPot2DMipMap | 
													GraphicsExtension::DrawInstanced | 
													GraphicsExtension::InstancedArrays));

			// set internal state to nulls
			this->vertexBuffers.resize(4);
			this->textures.resize(4);
			
			
			this->minFrameDelta = std::make_unique<DeltaTime>(60);


#ifdef _DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback((GLDEBUGPROC) (GraphicsContext::ErrorCallback), nullptr);
#endif
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			this->SetError(PSM_ERROR_COMMON_INVALID_OPERATION);
		}
	}
}
