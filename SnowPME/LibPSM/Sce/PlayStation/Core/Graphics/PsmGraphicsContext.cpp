#include "PsmGraphicsContext.hpp"

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
	int PsmGraphicsContext::GetScreenSizes(ImageSize* sizes, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetScreenSizes(Sce::PlayStation::Core::Imaging::ImageSize*, int *) Unimplemented." << std::endl;
		return 0;
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
