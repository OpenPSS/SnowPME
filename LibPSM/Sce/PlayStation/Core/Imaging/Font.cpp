#include "Font.hpp"

namespace Sce::PlayStation::Core::Imaging {
	int Font::NewFromFilenameSizeStyle(std::string filename, int size, FontStyle style, int* handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int* handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::AddRefNative(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::ReleaseNative(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::GetName(int handle, std::string* name) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::GetSize(int handle, int* size) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::GetStyle(int handle, FontStyle* style) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::GetMetrics(int handle, FontMetrics* fontMetrics) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::GetTextWidthNative(int handle, std::string text, int offset, int len, int* width) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Font::GetTextMetricsNative(int handle, std::string text, int offset, int len, CharMetrics* charMetrics) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
