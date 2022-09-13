#include "Font.hpp"

namespace Sce::PlayStation::Core::Imaging {
	int Font::NewFromFilenameSizeStyle(string filename, int size, FontStyle style, int* handle) {
		cout << "Sce::PlayStation::Core::Imaging::NewFromFilenameSizeStyle(string, int, Sce::PlayStation::Core::Imaging::FontStyle, int *) Unimplemented." << endl;
		return 0;
	}
	int Font::NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int* handle) {
		cout << "Sce::PlayStation::Core::Imaging::NewFromAliasSizeStyle(Sce::PlayStation::Core::Imaging::FontAlias, int, Sce::PlayStation::Core::Imaging::FontStyle, int *) Unimplemented." << endl;
		return 0;
	}
	int Font::AddRefNative(int handle) {
		cout << "Sce::PlayStation::Core::Imaging::AddRefNative(int) Unimplemented." << endl;
		return 0;
	}
	int Font::ReleaseNative(int handle) {
		cout << "Sce::PlayStation::Core::Imaging::ReleaseNative(int) Unimplemented." << endl;
		return 0;
	}
	int Font::GetName(int handle, string* name) {
		cout << "Sce::PlayStation::Core::Imaging::GetName(int, string *) Unimplemented." << endl;
		return 0;
	}
	int Font::GetSize(int handle, int* size) {
		cout << "Sce::PlayStation::Core::Imaging::GetSize(int, int *) Unimplemented." << endl;
		return 0;
	}
	int Font::GetStyle(int handle, FontStyle* style) {
		cout << "Sce::PlayStation::Core::Imaging::GetStyle(int, Sce::PlayStation::Core::Imaging::FontStyle *) Unimplemented." << endl;
		return 0;
	}
	int Font::GetMetrics(int handle, FontMetrics* fontMetrics) {
		cout << "Sce::PlayStation::Core::Imaging::GetMetrics(int, Sce::PlayStation::Core::Imaging::FontMetrics *) Unimplemented." << endl;
		return 0;
	}
	int Font::GetTextWidthNative(int handle, string text, int offset, int len, int* width) {
		cout << "Sce::PlayStation::Core::Imaging::GetTextWidthNative(int, string, int, int, int *) Unimplemented." << endl;
		return 0;
	}
	int Font::GetTextMetricsNative(int handle, string text, int offset, int len, CharMetrics* charMetrics) {
		cout << "Sce::PlayStation::Core::Imaging::GetTextMetricsNative(int, string, int, int, Sce::PlayStation::Core::Imaging::CharMetrics*) Unimplemented." << endl;
		return 0;
	}
}
