#include <Sce/Pss/Core/Graphics/PsmGraphicsContext.hpp>

#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <mono/mono.h>
#include <LibShared.hpp>
#include <glad/glad.h>
#include <string.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Graphics {


	int PsmGraphicsContext::Create(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode, int* result) {
		Logger::Debug(__FUNCTION__);
		
		if (GraphicsContext::GetUniqueObject() != nullptr) {
			return PSM_ERROR_GRAPHICS_SYSTEM;
		}

		GraphicsContext* graphicsContext = new GraphicsContext(width, height, colorFormat, depthFormat, multiSampleMode);
		RETURN_ERRORABLE(graphicsContext);

		*result = Handles::Create(graphicsContext);
		
		return PSM_ERROR_NO_ERROR;
	}
	int PsmGraphicsContext::Delete(int handle){
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetUniqueObject() == nullptr) return PSM_ERROR_GRAPHICS_SYSTEM;
			delete GraphicsContext::GetUniqueObject();
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::Update(int handle, GraphicsUpdate update, GraphicsState* state, MonoArray* handles) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			GraphicsContext* ctx = GraphicsContext::GetUniqueObject();
			if (ctx == nullptr) return PSM_ERROR_GRAPHICS_SYSTEM;

			int* handlesList = NULL;

			if (handles) {
				handlesList = (int*)mono_array_addr_with_size(handles, 1, 0);
			}


			return ctx->Update(update, state, handlesList);
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::SwapBuffers(int handle){
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			GraphicsContext* ctx = GraphicsContext::GetUniqueObject();
			if (ctx == nullptr) return PSM_ERROR_GRAPHICS_SYSTEM;

			ctx->SwapBuffers();
			// someotherfunction();

			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::Clear(int handle, ClearMask mask) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			GraphicsContext* ctx = GraphicsContext::GetUniqueObject();
			if (ctx == nullptr) return PSM_ERROR_GRAPHICS_SYSTEM;

			return ctx->Clear(mask);
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::DrawArrays(int handle, DrawMode mode, int first, int count, int repeat){
		UNIMPLEMENTED();
	}
	int PsmGraphicsContext::DrawArrays2(int handle, Primitive* primitives, int first, int count){
		UNIMPLEMENTED();
	}
	int PsmGraphicsContext::DrawArraysInstanced(int handle, DrawMode mode, int first, int count, int instFirst, int instCount){
		UNIMPLEMENTED();
	}
	int PsmGraphicsContext::ReadPixels(int handle, uint8_t* pixels, PixelFormat format, int sx, int sy, int sw, int sh){
		UNIMPLEMENTED();
	}
	int PsmGraphicsContext::ReadPixels2(int handle, int texture, int level, TextureCubeFace cubeFace, int dx, int dy, int sx, int sy, int sw, int sh) {
		UNIMPLEMENTED();
	}
	int PsmGraphicsContext::GetMaxScreenSize(int* width, int* height) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetUniqueObject() == NULL) return PSM_ERROR_GRAPHICS_SYSTEM;
			*height = Shared::Config::ScreenHeight(0);
			*width = Shared::Config::ScreenWidth(0);
			Logger::Debug("width: " + std::to_string(*width) + " height: " + std::to_string(*height));
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::GetScreenSizes(MonoArray* sizes, int* result) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetUniqueObject() == NULL) return PSM_ERROR_GRAPHICS_SYSTEM;
			int numScreens = Shared::Config::ScreenTotal;
			Logger::Debug("numScreens: " + std::to_string(numScreens));
			if (sizes) {
				uintptr_t arraySize = mono_array_length(sizes);
				ImageSize* imgsizes = (ImageSize*)mono_array_addr_with_size(sizes, 0, 1);
				for (uint32_t i = 0; i < arraySize; i++) {

					int height = Shared::Config::ScreenHeight(i);
					int width = Shared::Config::ScreenWidth(i);
					Logger::Debug("width(" + std::to_string(i) + ") : " + std::to_string(width) + " height(" + std::to_string(i) + ") : " + std::to_string(height));

					imgsizes[i].Height = height;
					imgsizes[i].Width = width;
				}
			}

			*result = numScreens;
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::GetScreenInfo(int handle, int* width, int* height, PixelFormat* colorFormat, PixelFormat* depthFormat, MultiSampleMode* multiSampleMode) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetUniqueObject() == NULL) return PSM_ERROR_GRAPHICS_SYSTEM;

			*width = GraphicsContext::GetUniqueObject()->Width;
			*height = GraphicsContext::GetUniqueObject()->Height;
			*colorFormat = GraphicsContext::GetUniqueObject()->ColorFormat;
			*depthFormat = GraphicsContext::GetUniqueObject()->DepthFormat;
			*multiSampleMode = GraphicsContext::GetUniqueObject()->SampleMode;

			Logger::Debug("width/height/colorFormat/depthFormat/multiSampleMode " + std::to_string(*width) + " " + std::to_string(*height) + " " + std::to_string((uint32_t)*colorFormat) + " " + std::to_string((uint32_t)*depthFormat) + " " + std::to_string((uint32_t)*multiSampleMode));

			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::GetCaps(int handle, GraphicsCapsState* caps) {
		Logger::Debug(__FUNCTION__);
		if (GraphicsContext::GetUniqueObject() == NULL) return PSM_ERROR_GRAPHICS_SYSTEM;
		if (Thread::IsMainThread()) {
			memcpy(caps, GraphicsContext::GetUniqueObject()->CapsState, sizeof(GraphicsCapsState));
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::SetActiveScreen(int handle, int x, int y, int w, int h) {
		UNIMPLEMENTED();
	}
	int PsmGraphicsContext::SetVirtualScreen(int handle, int x, int y, int w, int h) {
		UNIMPLEMENTED();
	}
}
