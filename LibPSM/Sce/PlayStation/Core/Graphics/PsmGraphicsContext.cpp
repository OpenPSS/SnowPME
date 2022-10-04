#include "PsmGraphicsContext.hpp"
#include <mono/mono.h>
#include <LibSnowPME.hpp>
#include "../Error.hpp"
using namespace SnowPME::Debug;
using namespace SnowPME::Util;

namespace Sce::PlayStation::Core::Graphics {
	int PsmGraphicsContext::Create(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::Create(int, int, Sce::PlayStation::Core::Graphics::PixelFormat, Sce::PlayStation::Core::Graphics::PixelFormat, Sce::PlayStation::Core::Graphics::MultiSampleMode, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::Delete(int handle){
		std::cout << "Sce::PlayStation::Core::Graphics::Delete(int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::Update(int handle, GraphicsUpdate update, GraphicsState* state, int* handles) {
		std::cout << "Sce::PlayStation::Core::Graphics::Update(int, Sce::PlayStation::Core::Graphics::GraphicsUpdate, Sce::PlayStation::Core::Graphics::GraphicsState *, int*) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::SwapBuffers(int handle){
		std::cout << "Sce::PlayStation::Core::Graphics::SwapBuffers(int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::Clear(int handle, ClearMask mask) {
		std::cout << "Sce::PlayStation::Core::Graphics::Clear(int, Sce::PlayStation::Core::Graphics::ClearMask) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::DrawArrays(int handle, DrawMode mode, int first, int count, int repeat){
		std::cout << "Sce::PlayStation::Core::Graphics::DrawArrays(int, Sce::PlayStation::Core::Graphics::DrawMode, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::DrawArrays2(int handle, Primitive* primitives, int first, int count){
		std::cout << "Sce::PlayStation::Core::Graphics::DrawArrays2(int, Sce::PlayStation::Core::Graphics::Primitive*, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::DrawArraysInstanced(int handle, DrawMode mode, int first, int count, int instFirst, int instCount){
		std::cout << "Sce::PlayStation::Core::Graphics::DrawArraysInstanced(int, Sce::PlayStation::Core::Graphics::DrawMode, int, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::ReadPixels(int handle, std::byte* pixels, PixelFormat format, int sx, int sy, int sw, int sh){
		std::cout << "Sce::PlayStation::Core::Graphics::ReadPixels(int, byte*, Sce::PlayStation::Core::Graphics::PixelFormat, int, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::ReadPixels2(int handle, int texture, int level, TextureCubeFace cubeFace, int dx, int dy, int sx, int sy, int sw, int sh) {
		std::cout << "Sce::PlayStation::Core::Graphics::ReadPixels2(int, int, int, Sce::PlayStation::Core::Graphics::TextureCubeFace, int, int, int, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::GetMaxScreenSize(int* width, int* height) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetMaxScreenSize(int *, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::GetScreenSizes(MonoArray* sizes, int* result) {
		Logger::Debug(__func__);
		if (THREAD_CHECK) {
			int numScreens = Config::ScreenTotal();
			if (sizes) {
				uintptr_t arraySize = mono_array_length(sizes);
				for (uint32_t i = 0; i < arraySize; i++) {
					ImageSize* imgsize = (ImageSize*)mono_array_addr_with_size(sizes, sizeof(ImageSize), i);

					imgsize->Height = Config::ScreenHeight(i);
					imgsize->Width = Config::ScreenWidth(i);
				}
			}

			*result = numScreens;
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error(std::string(__func__) + " cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmGraphicsContext::GetScreenInfo(int handle, int* width, int* height, PixelFormat* colorFormat, PixelFormat* depthFormat, MultiSampleMode* multiSampleMode) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetScreenInfo(int, int *, int *, Sce::PlayStation::Core::Graphics::PixelFormat *, Sce::PlayStation::Core::Graphics::PixelFormat *, Sce::PlayStation::Core::Graphics::MultiSampleMode *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::GetCaps(int handle, GraphicsCapsState* caps) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetCaps(int, Sce::PlayStation::Core::Graphics::GraphicsCapsState *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::SetActiveScreen(int handle, int x, int y, int w, int h) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetActiveScreen(int, int, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmGraphicsContext::SetVirtualScreen(int handle, int x, int y, int w, int h) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetVirtualScreen(int, int, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
}
