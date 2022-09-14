#include "Font.hpp"

namespace Sce::PlayStation::Core::Imaging {
	int Font::NewFromFilenameSizeStyle(std::string filename, int size, FontStyle style, int* handle) {
		std::cout << "Sce::PlayStation::Core::Imaging::NewFromFilenameSizeStyle(string, int, Sce::PlayStation::Core::Imaging::FontStyle, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Font::NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int* handle) {
		std::cout << "Sce::PlayStation::Core::Imaging::NewFromAliasSizeStyle(Sce::PlayStation::Core::Imaging::FontAlias, int, Sce::PlayStation::Core::Imaging::FontStyle, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Font::AddRefNative(int handle) {
		std::cout << "Sce::PlayStation::Core::Imaging::AddRefNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int Font::ReleaseNative(int handle) {
		std::cout << "Sce::PlayStation::Core::Imaging::ReleaseNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int Font::GetName(int handle, std::string* name) {
		std::cout << "Sce::PlayStation::Core::Imaging::GetName(int, string *) Unimplemented." << std::endl;
		return 0;
	}
	int Font::GetSize(int handle, int* size) {
		std::cout << "Sce::PlayStation::Core::Imaging::GetSize(int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Font::GetStyle(int handle, FontStyle* style) {
		std::cout << "Sce::PlayStation::Core::Imaging::GetStyle(int, Sce::PlayStation::Core::Imaging::FontStyle *) Unimplemented." << std::endl;
		return 0;
	}
	int Font::GetMetrics(int handle, FontMetrics* fontMetrics) {
		std::cout << "Sce::PlayStation::Core::Imaging::GetMetrics(int, Sce::PlayStation::Core::Imaging::FontMetrics *) Unimplemented." << std::endl;
		return 0;
	}
	int Font::GetTextWidthNative(int handle, std::string text, int offset, int len, int* width) {
		std::cout << "Sce::PlayStation::Core::Imaging::GetTextWidthNative(int, string, int, int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int Font::GetTextMetricsNative(int handle, std::string text, int offset, int len, CharMetrics* charMetrics) {
		std::cout << "Sce::PlayStation::Core::Imaging::GetTextMetricsNative(int, string, int, int, Sce::PlayStation::Core::Imaging::CharMetrics*) Unimplemented." << std::endl;
		return 0;
	}
}
