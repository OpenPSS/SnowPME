#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsExtension.hpp>
#include <Sce/Pss/Core/Graphics/ColorMask.hpp>

#include <Sce/Pss/Core/Event/PsmEventQueue.hpp>
#include <Sce/Pss/Core/Event/PsmEvent.hpp>
#include <Sce/Pss/Core/Event/PsmEventType.hpp>

#include <glad/glad.h>
#include <LibShared.hpp>
#include <string.h>
#include <math.h>

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Event;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	int GraphicsContext::ActiveStateChanged(bool state) {
		return PSM_ERROR_NOT_IMPLEMENTED;
	}

	int GraphicsContext::setCurrentObject(ShaderProgram* shaderProgram) {
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
	int GraphicsContext::setCurrentObject(FrameBuffer* frameBuffer) {
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
				ShaderProgram* workingShaderProgram = Handles::Get<ShaderProgram>(handles[GraphicsContext::shaderProgramHandleOffset]);
				
				// Set this shader program as the currently active shader program.
				setCurrentObject(workingShaderProgram);
			}

			// check update is a FrameBuffer
			if ((update & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::FrameBuffer");

				int fbHandle = handles[GraphicsContext::frameBufferHandleOffset];
				// Check this handle is valid ..
				if (fbHandle != Handles::NoHandle) {
					// Resolve the handle for the new shader program
					FrameBuffer* workingFrameBuffer = Handles::Get<FrameBuffer>(fbHandle);

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
					VertexBuffer* workingVertexBuffer = Handles::Get<VertexBuffer>(handles[GraphicsContext::vertexBufferHandleOffset + i]);
					VertexBuffer* currentVertexBuffer = (VertexBuffer*)this->currentVertexBuffers[i];

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

						this->currentVertexBuffers[i] = workingVertexBuffer;

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
				Logger::Error("update & GraphicsUpdate::Texture is not implemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
			}

		}

		this->NotifyUpdate(update);
		this->CheckUpdate(state);
		return PSM_ERROR_NO_ERROR;
	}

	void GraphicsContext::UpdateHandles(GraphicsUpdate notifyFlag) {
		Logger::Debug(__FUNCTION__);
		// check notifyFlag is ShaderProgram .
		if ((notifyFlag & GraphicsUpdate::ShaderProgram) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::ShaderProgram");

			// bind the current program in openGL
			OpenGL::SetShaderProgram(this->currentProgram);

			// set the vertexBuffer notify flag.
			notifyFlag = notifyFlag | GraphicsUpdate::VertexBuffer;
		}

		// check notifyFlag is VertexBuffer
		if ((notifyFlag & GraphicsUpdate::VertexBuffer) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::VertexBuffer");

			Logger::Error("notifyFlag VertexBuffer part is not yet implemented;");
			this->SetError(PSM_ERROR_NOT_IMPLEMENTED);
			return;
		}

		// check notifyFlag is Texture
		if ((notifyFlag & GraphicsUpdate::Texture) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::Texture");

			Logger::Error("notifyFlag Texture part is not yet implemented;");
			this->SetError(PSM_ERROR_NOT_IMPLEMENTED);
			return;
		}

		// check notifyFlag is FrameBuffer
		if ((notifyFlag & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::FrameBuffer");

			// bind the framebuffer
			OpenGL::SetFrameBuffer(this->currentFrameBuffer);
			
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
			ExceptionInfo::AddMessage("Frame buffer is not available");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	
	int GraphicsContext::EndFrame() {
		if (Threading::Thread::IsMainThread() /* && !endframe_related_ns && endframe_related_0 && endframe_related */) {
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
		if (Threading::Thread::IsMainThread() /* || endframe_related_ns || startframe_related || !endframe_related_0 || !endframe_related */) {
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

		PsmEventQueue::IncomingEventQueue.Push(new PsmEvent(PsmEventType::SwapBuffers));

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

		double deltaTime = minFrameDelta->CalculateDelta();
		if (deltaTime < minFrameDelta->MinDelta()) {
			double maxSleepTime = (1 / 16);
			deltaTime -= maxSleepTime;
			Thread::Sleep(deltaTime);
			minFrameDelta->CalculateDelta();
		}

		return PSM_ERROR_NO_ERROR;
	}

	void GraphicsContext::UpdateState(GraphicsUpdate notifyFlag, GraphicsState* state) {
		Logger::Debug(__FUNCTION__);

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
				glScissor(state->Scissor.X, state->Scissor.Y, state->Scissor.Width, state->Scissor.Y);
			}

			if ((notifyFlag & GraphicsUpdate::Viewport) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::Viewport");

				// Set OpenGL viewport,
				// if the width or height is less than 0, then the height/width is set to 0.

				glViewport(
					state->Viewport.X,
					state->Viewport.Y,
					state->Viewport.Width < 0 ? 0 : state->Viewport.Width,
					state->Viewport.Height < 0 ? 0 : state->Viewport.Height);


			}

			if ((notifyFlag & GraphicsUpdate::DepthRange) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::DepthRange");
				// Set OpenGL Depth Range
				
				glDepthRangef(state->DepthRange.X, state->DepthRange.Y);

			}

			if ((notifyFlag & GraphicsUpdate::ClearColor) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ClearColor");
				// Set OpenGL Clear Color

				glClearColor(state->ClearColor.X, state->ClearColor.Y, state->ClearColor.Z, state->ClearColor.W);
			}

			if ((notifyFlag & GraphicsUpdate::ClearDepth) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ClearDepth");
				// Set OpenGL Clear Depth

				glClearDepthf(state->ClearDepth);
			}

			if ((notifyFlag & GraphicsUpdate::ClearStencil) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ClearStencil");
				// Set OpenGL Clear Stencil

				glClearStencil(state->ClearStencil);
			}

		}
			
		if ((notifyFlag & 0xE000) != GraphicsUpdate::None) { // TODO: work out what 0xE000 is.
			if ((notifyFlag & GraphicsUpdate::ColorMask) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::ColorMask");

				using namespace Sce::Pss::Core::Graphics;

				glColorMask(
					(state->ColorMask & ColorMask::R) != Sce::Pss::Core::Graphics::ColorMask::None,
					(state->ColorMask & ColorMask::G) != Sce::Pss::Core::Graphics::ColorMask::None,
					(state->ColorMask & ColorMask::B) != Sce::Pss::Core::Graphics::ColorMask::None,
					(state->ColorMask & ColorMask::A) != Sce::Pss::Core::Graphics::ColorMask::None);

			}

			if ((notifyFlag & GraphicsUpdate::LineWidth) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::LineWidth");

				float lnAdd = state->LineWidth + 0.5;
				float lnFloor = floor(lnAdd);
				float lnBase = 1.0;
				if (lnFloor >= 1.0)
				{
					lnBase = lnFloor;
					if (lnFloor > 8.0)
						lnBase = 8.0;
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
				glCullFace(this->glCullModes[state->CullFace.bits & 3]);
				glFrontFace(this->glCullFrontFaceModes[(state->CullFace.bits >> 8) & 1]);

				if (state->CullFace.bits & 0xFF)
					this->cullFaceBits |=  2;
				else
					this->cullFaceBits |= 0xFFFFFFFD;
			}

			if ((notifyFlag & GraphicsUpdate::BlendFunc) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::BlendFunc");
				glBlendEquationSeparate(
					this->glBlendModes[state->BlendFuncRgb.bits & 3],
					this->glBlendModes[state->BlendFuncAlpha.bits & 3]);
				glBlendFuncSeparate(
					this->glBlendSFactor[(state->BlendFuncRgb.bits >> 8) & 0xF],
					this->glBlendDFactor[(state->BlendFuncRgb.bits & 0x0000FFFF) & 0xF],
					this->glBlendSFactor[(state->BlendFuncAlpha.bits >> 8) & 0xF],
					this->glBlendDFactor[(state->BlendFuncAlpha.bits & 0x0000FFFF) & 0xF]);
			}

			if ((notifyFlag & GraphicsUpdate::DepthFunc) != GraphicsUpdate::None)
			{
				Logger::Debug("notifyFlag & GraphicsUpdate::DepthFunc");
				glDepthFunc(glDepthFuncs[state->DepthFunc.bits & 7]);
				glDepthMask((state->DepthFunc.bits >> 8) & 0xFF);
			}
			if ((notifyFlag & GraphicsUpdate::PolygonOffset) != GraphicsUpdate::None) {
				Logger::Debug("notifyFlag & GraphicsUpdate::PolygonOffset");
				glPolygonOffset(state->PolygonOffset.Factor, state->PolygonOffset.Units);
			}
			if ((notifyFlag & GraphicsUpdate::StencilFunc) != GraphicsUpdate::None)
			{
				Logger::Debug("notifyFlag & GraphicsUpdate::StencilFunc");
				
				glStencilFuncSeparate(GL_FRONT, 
									glDepthFuncs[state->StencilFuncFront.bits & 7],
									(state->StencilFuncFront.bits >> 8) & 0xFF,
									(state->StencilFuncFront.bits >> 16) & 0xFF
				);

				glStencilFuncSeparate(GL_BACK,
									glDepthFuncs[state->StencilFuncBack.bits & 7],
									(state->StencilFuncBack.bits >> 8) & 0xFF,
									(state->StencilFuncBack.bits >> 16) & 0xFF
				);

				glStencilMaskSeparate(GL_FRONT, (state->StencilFuncFront.bits >> 24) & 0xFF);
				glStencilMaskSeparate(GL_BACK, (state->StencilFuncBack.bits >> 24) & 0xFF);

			}
			if ((notifyFlag & GraphicsUpdate::StencilOp) != GraphicsUpdate::None)
			{
				Logger::Debug("notifyFlag & GraphicsUpdate::StencilOp");

				glStencilOpSeparate(
					GL_FRONT,
					glStencilOps[state->StencilOpFront.bits & 7],
					glStencilOps[(state->StencilOpFront.bits >> 8) & 7],
					glStencilOps[((state->StencilOpFront.bits >> 16) & 0xFFFF) & 7]
				);
				glStencilOpSeparate(
					GL_BACK,
					glStencilOps[state->StencilOpBack.bits & 7],
					glStencilOps[(state->StencilOpBack.bits >> 8) & 7],
					glStencilOps[((state->StencilOpBack.bits >> 16) & 0xFFFF) & 7]
				);
			}

		}

		if ((notifyFlag & GraphicsUpdate::Enable) != GraphicsUpdate::None) {
			Logger::Debug("notifyFlag & GraphicsUpdate::Enable");
			EnableMode enableModeToggleFlags = (state->Enable & this->cullFaceBits);
			EnableMode enableModeBitlist = (enableModeToggleFlags ^ this->currentEnableModes) & EnableMode::All;
			
			if (this->currentEnableModes == (EnableMode)0xFF) {
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
		if(this->minFrameDelta != nullptr)
			delete this->minFrameDelta;
	}
	void GraphicsContext::ErrorCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam) {
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

			std::vector<std::string> extensionList = Shared::String::StringUtil::Split(this->Extensions, " ");

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

			memset(this->currentVertexBuffers, NULL, sizeof(GraphicsContext::currentVertexBuffers));
			memset(this->currentTextures, NULL, sizeof(GraphicsContext::currentTextures));

			this->minFrameDelta = new Sce::Pss::Core::Timing::DeltaTime(60);

#ifdef _DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback((GLDEBUGPROC) (GraphicsContext::ErrorCallback), nullptr);
#endif
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
			this->SetError(PSM_ERROR_COMMON_INVALID_OPERATION);
		}
	}
}
