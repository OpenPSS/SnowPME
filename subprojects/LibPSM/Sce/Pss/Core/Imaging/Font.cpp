#include <Sce/Pss/Core/Imaging/Font.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Imaging {
	int Font::NewFromFilenameSizeStyle(std::string filename, int size, FontStyle style, int* handle) {
		Unimplemented();
	}
	int Font::NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int* handle) {
		Unimplemented();
	}
	int Font::AddRefNative(int handle) {
		Unimplemented();
	}
	int Font::ReleaseNative(int handle) {
		Unimplemented();
	}
	int Font::GetName(int handle, std::string* name) {
		Unimplemented();
	}
	int Font::GetSize(int handle, int* size) {
		Unimplemented();
	}
	int Font::GetStyle(int handle, FontStyle* style) {
		Unimplemented();
	}
	int Font::GetMetrics(int handle, FontMetrics* fontMetrics) {
		Unimplemented();
	}
	int Font::GetTextWidthNative(int handle, std::string text, int offset, int len, int* width) {
		Unimplemented();
	}
	int Font::GetTextMetricsNative(int handle, std::string text, int offset, int len, CharMetrics* charMetrics) {
		Unimplemented();
	}
}
