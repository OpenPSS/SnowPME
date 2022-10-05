#include "PsmGraphicsContext.hpp"
#include <mono/mono.h>
#include <LibSnowPME.hpp>
#include <glad/glad.h>
#include "../Error.hpp"
using namespace SnowPME::Debug;
using namespace SnowPME::Util;

namespace Sce::PlayStation::Core::Graphics {
	static GraphicsContext* currentContext = NULL;
	GraphicsContext* PsmGraphicsContext::GetContext() {
		return currentContext;
	}
	int PsmGraphicsContext::Create(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode, int* result) {
		Logger::Debug(__FUNCTION__);

		if (!CTX_CHECK) return PSM_ERROR_GRAPHICS_SYSTEM;

		GraphicsContext* context = new GraphicsContext();
		context->Width = width;
		context->Height = height;
		context->ColorFormat = colorFormat;
		context->DepthFormat = depthFormat;
		context->MultiSampleMode = multiSampleMode;
		context->MainWindow = AppGlobals::PsmMainWindow();
		context->CapsState = new GraphicsCapsState();
		
		context->ThreadId = PlatformSpecific::CurrentThreadId();
			
		// Set width/height
		if(width == 0)
			context->Width = Config::ScreenWidth(0);
		if(height == 0)
			context->Height = Config::ScreenHeight(0);

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
			context->DepthFormat = PixelFormat::None;

			if (depthBits >= 16)
				context->DepthFormat = (stencilBits >= 8) ? PixelFormat::Depth16Stencil8 : PixelFormat::Depth16;
			if (depthBits >= 24)
				context->DepthFormat = (stencilBits >= 8) ? PixelFormat::Depth24Stencil8 : PixelFormat::Depth24;
		}

		if (colorFormat == PixelFormat::None) {
			context->ColorFormat = PixelFormat::Rgb565;
			if (redBits >= 8 && greenBits >= 8 && blueBits >= 8 && alphaBits >= 8)
				context->ColorFormat = PixelFormat::Rgba;
		}

		if (multiSampleMode == MultiSampleMode::None) {
			context->MultiSampleMode = MultiSampleMode::None;
			if (glSamples >= 2)
				context->MultiSampleMode = MultiSampleMode::Msaa2x;
			if (glSamples >= 4)
				context->MultiSampleMode = MultiSampleMode::Msaa4x;
		}

		// Populate CapsState

		glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &context->CapsState->MaxViewportWidth);
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &context->CapsState->MaxTextureSize);
		glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &context->CapsState->MaxCubeMapTextureSize);
		glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &context->CapsState->MaxRenderbufferSize);
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &context->CapsState->MaxVertexUniformVectors);
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &context->CapsState->MaxFragmentUniformVectors);
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &context->CapsState->MaxVertexAttribs);
		glGetIntegerv(GL_MAX_VARYING_VECTORS, &context->CapsState->MaxVaryingVectors);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &context->CapsState->MaxCombinedTextureImageUnits);
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &context->CapsState->MaxTextureImageUnits);
		glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &context->CapsState->MaxVertexTextureImageUnits);

		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &context->CapsState->MaxTextureMaxAnisotropy);
		glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, &context->CapsState->MinAliasedLineWidth);
		glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, &context->CapsState->MinAliasedPointSize);

		context->Extensions = std::string((char*)glGetString(GL_EXTENSIONS));
		std::vector<std::string> extensionList = StringUtils::Split(context->Extensions, " ");

		Logger::Info("GLES2 Vendor: " + std::string((char*)glGetString(GL_VENDOR)));
		Logger::Info("GLES2 Renderer: " + std::string((char*)glGetString(GL_RENDERER)));
		Logger::Info("GLES2 Version: " + std::string((char*)glGetString(GL_VERSION)));
		Logger::Info("GLES2 Shader Language Version: " + std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));

		context->Renderer = std::string((char*)glGetString(GL_RENDERER));

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
		if (context->CapsState->MaxTextureSize > 0x800)
			context->CapsState->MaxTextureSize = 0x800;
		if (context->CapsState->MaxCubeMapTextureSize > 0x800)
			context->CapsState->MaxCubeMapTextureSize = 0x800;
		if (context->CapsState->MaxRenderbufferSize > 0x800)
			context->CapsState->MaxRenderbufferSize = 0x800;
		if (context->CapsState->MaxVertexUniformVectors > 0x80)
			context->CapsState->MaxVertexUniformVectors = 0x80;
		if (context->CapsState->MaxFragmentUniformVectors > 0x40)
			context->CapsState->MaxFragmentUniformVectors = 0x40;
		if (context->CapsState->MaxVertexAttribs > 0x8)
			context->CapsState->MaxVertexAttribs = 0x8;
		if (context->CapsState->MaxVaryingVectors > 0x8)
			context->CapsState->MaxVaryingVectors = 0x8;
		if (context->CapsState->MaxCombinedTextureImageUnits > 0x8)
			context->CapsState->MaxCombinedTextureImageUnits = 0x8;
		if (context->CapsState->MaxTextureImageUnits > 0x8)
			context->CapsState->MaxTextureImageUnits = 0x8;
		if (context->CapsState->MaxVertexTextureImageUnits > 0x0)
			context->CapsState->MaxVertexTextureImageUnits = 0x0;

		if (context->CapsState->MaxAliasedLineWidth > 8.0)
			context->CapsState->MaxAliasedLineWidth = 8.0;
		if (context->CapsState->MaxAliasedPointSize > 128.0)
			context->CapsState->MaxAliasedPointSize = 128.0;

		context->CapsState->Extension = (gext & 0x3A9B8);

		currentContext = context;

		return PSM_ERROR_NO_ERROR;
	}
	int PsmGraphicsContext::Delete(int handle){
		Logger::Debug(__FUNCTION__);
		if (CTX_CHECK) return PSM_ERROR_GRAPHICS_SYSTEM;
		if (THREAD_CHECK) {
			
			delete currentContext->CapsState;
			delete currentContext;

			currentContext = NULL;
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::Update(int handle, GraphicsUpdate update, GraphicsState* state, int* handles) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::SwapBuffers(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::Clear(int handle, ClearMask mask) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::DrawArrays(int handle, DrawMode mode, int first, int count, int repeat){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::DrawArrays2(int handle, Primitive* primitives, int first, int count){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::DrawArraysInstanced(int handle, DrawMode mode, int first, int count, int instFirst, int instCount){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::ReadPixels(int handle, std::byte* pixels, PixelFormat format, int sx, int sy, int sw, int sh){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::ReadPixels2(int handle, int texture, int level, TextureCubeFace cubeFace, int dx, int dy, int sx, int sy, int sw, int sh) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::GetMaxScreenSize(int* width, int* height) {
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			*height = Config::ScreenHeight(0);
			*width = Config::ScreenWidth(0);
			Logger::Debug("width: " + std::to_string(*width) + " height: " + std::to_string(*height));
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::GetScreenSizes(MonoArray* sizes, int* result) {
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			int numScreens = Config::ScreenTotal();
			Logger::Debug("numScreens: " + std::to_string(numScreens));
			if (sizes) {
				uintptr_t arraySize = mono_array_length(sizes);
				for (uint32_t i = 0; i < arraySize; i++) {
					ImageSize* imgsize = (ImageSize*)mono_array_addr_with_size(sizes, sizeof(ImageSize), i);

					int height = Config::ScreenHeight(i);
					int width = Config::ScreenWidth(i);
					Logger::Debug("width(" + std::to_string(i) + ") : " + std::to_string(width) + " height(" + std::to_string(i) + ") : " + std::to_string(height));

					imgsize->Height = height;
					imgsize->Width = width;
				}
			}

			*result = numScreens;
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::GetScreenInfo(int handle, int* width, int* height, PixelFormat* colorFormat, PixelFormat* depthFormat, MultiSampleMode* multiSampleMode) {
		Logger::Debug(__FUNCTION__);
		if (CTX_CHECK) return PSM_ERROR_GRAPHICS_SYSTEM;
		if (THREAD_CHECK) {
			*width = GetContext()->Width;
			*height = GetContext()->Height;
			*(uint32_t*)colorFormat = (uint32_t)GetContext()->ColorFormat;
			*(uint32_t*)depthFormat = (uint32_t)GetContext()->DepthFormat;
			*(uint32_t*)multiSampleMode = (uint32_t)GetContext()->MultiSampleMode;

			Logger::Debug("width/height/colorFormat/depthFormat/multiSampleMode " + std::to_string(*width) + " " + std::to_string(*height) + " " + std::to_string((uint32_t)*colorFormat) + " " + std::to_string((uint32_t)*depthFormat) + " " + std::to_string((uint32_t)*multiSampleMode));

			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::GetCaps(int handle, GraphicsCapsState* caps) {
		Logger::Debug(__FUNCTION__);
		if (CTX_CHECK) return PSM_ERROR_GRAPHICS_SYSTEM;
		if (THREAD_CHECK) {
			GraphicsContext* context = (GraphicsContext*)handle;
			memcpy(caps, GetContext()->CapsState, sizeof(GraphicsCapsState));
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error(std::string(__FUNCTION__) + " cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::SetActiveScreen(int handle, int x, int y, int w, int h) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmGraphicsContext::SetVirtualScreen(int handle, int x, int y, int w, int h) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
