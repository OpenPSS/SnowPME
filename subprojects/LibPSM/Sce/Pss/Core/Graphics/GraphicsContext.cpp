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

	GraphicsCapsState GraphicsContext::capsState;

	const GLenum GraphicsContext::glEnableModes[0x7] = { GL_SCISSOR_TEST, GL_CULL_FACE, GL_BLEND, GL_DEPTH_TEST,
							                           GL_POLYGON_OFFSET_FILL, GL_STENCIL_TEST, GL_DITHER };
	const GLenum GraphicsContext::glStencilOps[0x8] = { GL_KEEP, GL_ZERO, GL_REPLACE, GL_INVERT,
								                      GL_INCR, GL_DECR, GL_INCR_WRAP, GL_DECR_WRAP };
	const GLenum GraphicsContext::glDepthFuncs[0x8] = { GL_ALWAYS, GL_NEVER, GL_EQUAL, GL_NOTEQUAL, GL_LESS,
								                      GL_GREATER, GL_LEQUAL, GL_GEQUAL };
	const GLenum GraphicsContext::glBlendModes[0x4] = { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD };

	const GLenum GraphicsContext::glBlendSFactor[0x10] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
									                     GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
									                     GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE,
									                     GL_ZERO, GL_ZERO, GL_ZERO };

	const GLenum GraphicsContext::glBlendDFactor[0x10] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
									                     GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
									                     GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ZERO, GL_ZERO,
									                     GL_ZERO, GL_ZERO, GL_ZERO };
	const GLenum GraphicsContext::glCullModes[0x4] = { GL_BACK, GL_FRONT, GL_BACK, GL_FRONT_AND_BACK };
	const GLenum GraphicsContext::glCullFrontFaceModes[0x2] = { GL_CW, GL_CCW };


	int GraphicsContext::ActiveStateChanged(bool state) {
		UNIMPLEMENTED();
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
					result = this->currentProgram->ActiveStateChanged();
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
					result = this->currentFrameBuffer->ActiveStateChanged();
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


		// check if update is not VertexBuffer, Texture, VertexBuffer0, VertexBufferN, Texture0, or TextureN

		if ((update & 0xFFFF0000) != GraphicsUpdate::None)
		{
			// check update is a ShaderProgram
			if ((update & GraphicsUpdate::ShaderProgram) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::ShaderProgram");

				// Resolve the handle for the new shader program
				ShaderProgram* workingShaderProgram = ShaderProgram::LookupHandle(handles[GraphicsContext::shaderProgramHandleOffset]);
				
				// Set this shader program as the currently active shader program.
				setCurrentObject(workingShaderProgram);
			}

			// check update is a FrameBuffer
			if ((update & GraphicsUpdate::FrameBuffer) != GraphicsUpdate::None) {
				Logger::Debug("update & GraphicsUpdate::FrameBuffer");

				int fbHandle = handles[GraphicsContext::frameBufferHandleOffset];
				// Check this handle is valid ..
				if (FrameBuffer::CheckHandle(fbHandle)) {
					// Resolve the handle for the new shader program
					FrameBuffer* workingFrameBuffer = FrameBuffer::LookupHandle(fbHandle);

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
							this->currentFrameBuffer->ActiveStateChanged();
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
					VertexBuffer* workingVertexBuffer = VertexBuffer::LookupHandle(handles[GraphicsContext::vertexBufferHandleOffset + i]);
					VertexBuffer* currentVertexBuffer = this->vertexBuffers[i];

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
								currentVertexBuffer->ActiveStateChanged();
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
		return this->CheckUpdate(state);
	}

	int GraphicsContext::UpdateHandles(GraphicsUpdate notifyFlag) {
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
			ShaderProgram* program = this->currentProgram;
			
			int numAttributes = 0;
			if (program != nullptr) {
				int numAttributes = program->Attributes.size();
			}

			VertexBuffer* vertexBuffer = this->vertexBuffers[0];

			int numStreams = 0;
			if (vertexBuffer != nullptr) {
				numStreams = vertexBuffer->FormatsLength;
			}

			// TODO: what are these?
			int unk1 = 0xFFFF;
			int unk2 = 0xFFFF;

			OpenGL::SetVertexBuffer(vertexBuffer);

			if (numAttributes > 0) {

				for (int i = 0; i < numAttributes; i++) {
					int stream = program->GetAttributeStream(i);
					if (stream >= 0) {
						// set the specified stream ..
						if (stream >= numStreams) {
							for (int strId = 0; strId < 4; strId++) {
								vertexBuffer = this->vertexBuffers[i];
								
								if (vertexBuffer != nullptr) {
									numStreams = vertexBuffer->FormatsLength;
									if (stream < numStreams) {
										if (strId > 0) numStreams = 0;
										OpenGL::SetVertexBuffer(vertexBuffer);
										break;
									}
								}

							}
						}
						else {
							VertexFormat format = vertexBuffer->VertexFormats[stream];
							if (format != VertexFormat::None) {
								if (vertexBuffer->VertexFormats[0] == VertexFormat::None) {
									if (unk2 > vertexBuffer->VertexCount) {
										unk2 = vertexBuffer->VertexCount;
									}
								}
								else if(unk1 > vertexBuffer->VertexCount) {
									unk1 = vertexBuffer->VertexCount;
								}

								Logger::Todo("index = *(_program->unk10 + 48 * *(v50 + _program->unk10) + 8)");
								// TODO: wtf is index = *(_program->unk10 + 48 * *(v50 + _program->unk10) + 8); 
								// ???
								
								int index = 0;
								if (index >= 0) {
									int vectorWidth = VertexBuffer::GetFormatVectorWidth(format);
									GLenum formatVectorType = OpenGL::GetVertexFormatType(format);
									GLenum formatVectorNormalized = OpenGL::GetVertexFormatNormalize(format);

									int stride = vertexBuffer->VertexBufferSize;
									
									Logger::Todo("pointer = *(vertexBuffer->unk14 + 4 * _stream);");

									/* TODO: wtf is this:
										pointer = *(vertexBuffer->unk14 + 4 * _stream);
										if ( vFormats )
										pointer += stride * this->unk24;
									*/

									void* pointer = nullptr;

									glVertexAttribPointer(index, vectorWidth, formatVectorType, formatVectorNormalized, stride, pointer);
									glVertexAttribDivisorEXT(index, static_cast<uint32_t>(vertexBuffer->VertexFormats[0]));
									glEnableVertexAttribArray(index);
								}
								


							}
						}
						Logger::Todo("Implement  goto i_greater_than_4; here.");
					}

				}
			}

			UNIMPLEMENTED_MSG("notifyFlag & GraphicsUpdate::VertexBuffer");
		}

		// check notifyFlag is Texture
		if ((notifyFlag & GraphicsUpdate::Texture) != GraphicsUpdate::None) {
			UNIMPLEMENTED_MSG("notifyFlag & GraphicsUpdate::Texture");
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

		return PSM_ERROR_NO_ERROR;
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

	int GraphicsContext::UpdateState(GraphicsUpdate notifyFlag, GraphicsState* state) {
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

		return PSM_ERROR_NO_ERROR;
	}

	int GraphicsContext::UpdateMultiScreen(GraphicsUpdate notifyFlag, GraphicsState* state, char unk) {
		UNIMPLEMENTED();
	}


	int GraphicsContext::CheckUpdate(GraphicsState* state) {
		GraphicsUpdate notifyFlag = this->updateNotifyFlag;
		int res = PSM_ERROR_NO_ERROR;
		if (this->updateNotifyFlag != GraphicsUpdate::None) {
			this->updateNotifyFlag = GraphicsUpdate::None;

			if ((notifyFlag & 0xFFFF0000) != GraphicsUpdate::None) {
				res = this->UpdateHandles(notifyFlag);
				if (res != PSM_ERROR_NO_ERROR) return res;
			}
			
			if (notifyFlag != GraphicsUpdate::None) {
				res = this->UpdateState(notifyFlag, state);
				if (res != PSM_ERROR_NO_ERROR) return res;
			}

			if (this->numScreens >= 2) {
				res = this->UpdateMultiScreen(notifyFlag, state, 0);
				if (res != PSM_ERROR_NO_ERROR) return res;
			}
		}

		return res;
	}

	GraphicsUpdate GraphicsContext::NotifyUpdateData(GraphicsUpdate updateDataFlag) {
		this->updateNotifyDataFlag = this->updateNotifyDataFlag | updateDataFlag;
		return updateNotifyDataFlag;
	}

	GraphicsUpdate GraphicsContext::NotifyUpdate(GraphicsUpdate updateFlag) {
		this->updateNotifyFlag = this->updateNotifyFlag | updateFlag;
		return updateFlag;
	}


	GraphicsCapsState& GraphicsContext::GetCaps() {
		return GraphicsContext::capsState;
	}

	GraphicsContext::GraphicsContext(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode) {

		if (Thread::IsMainThread()) {

			this->Width = width;
			this->Height = height;
			this->ColorFormat = colorFormat;
			this->DepthFormat = depthFormat;
			this->SampleMode = multiSampleMode;
			

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

			// Populate capsState

			glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &capsState.MaxViewportWidth);
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &capsState.MaxTextureSize);
			glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &capsState.MaxCubeMapTextureSize);
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &capsState.MaxRenderbufferSize);
			glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &capsState.MaxVertexUniformVectors);
			glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &capsState.MaxFragmentUniformVectors);
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &capsState.MaxVertexAttribs);
			glGetIntegerv(GL_MAX_VARYING_VECTORS, &capsState.MaxVaryingVectors);
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &capsState.MaxCombinedTextureImageUnits);
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &capsState.MaxTextureImageUnits);
			glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &capsState.MaxVertexTextureImageUnits);

			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &capsState.MaxTextureMaxAnisotropy);
			glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, &capsState.MinAliasedLineWidth);
			glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, &capsState.MinAliasedPointSize);

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

			GraphicsExtension gext = GraphicsExtension::None;
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
			if (capsState.MaxTextureSize > 0x800)
				capsState.MaxTextureSize = 0x800;
			if (capsState.MaxCubeMapTextureSize > 0x800)
				capsState.MaxCubeMapTextureSize = 0x800;
			if (capsState.MaxRenderbufferSize > 0x800)
				capsState.MaxRenderbufferSize = 0x800;
			if (capsState.MaxVertexUniformVectors > 0x80)
				capsState.MaxVertexUniformVectors = 0x80;
			if (capsState.MaxFragmentUniformVectors > 0x40)
				capsState.MaxFragmentUniformVectors = 0x40;
			if (capsState.MaxVertexAttribs > 0x8)
				capsState.MaxVertexAttribs = 0x8;
			if (capsState.MaxVaryingVectors > 0x8)
				capsState.MaxVaryingVectors = 0x8;
			if (capsState.MaxCombinedTextureImageUnits > 0x8)
				capsState.MaxCombinedTextureImageUnits = 0x8;
			if (capsState.MaxTextureImageUnits > 0x8)
				capsState.MaxTextureImageUnits = 0x8;
			if (capsState.MaxVertexTextureImageUnits > 0x0)
				capsState.MaxVertexTextureImageUnits = 0x0;

			if (capsState.MaxAliasedLineWidth > 8.0)
				capsState.MaxAliasedLineWidth = 8.0;
			if (capsState.MaxAliasedPointSize > 128.0)
				capsState.MaxAliasedPointSize = 128.0;

			capsState.Extension = (gext & (GraphicsExtension::TextureFilterAnisotropic |
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
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			this->SetError(PSM_ERROR_COMMON_INVALID_OPERATION);
		}
	}
}
