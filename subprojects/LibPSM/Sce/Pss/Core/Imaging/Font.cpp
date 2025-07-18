#include <Sce/Pss/Core/Imaging/Font.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Imaging {
	int Font::NewFromFilenameSizeStyle(MonoString* filename, int size, FontStyle style, int* handle) {
		UNIMPLEMENTED();
	}
	int Font::NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int* handle) {
		UNIMPLEMENTED();
	}
	int Font::AddRefNative(int handle) {
		UNIMPLEMENTED();
	}
	int Font::ReleaseNative(int handle) {
		UNIMPLEMENTED();
	}
	int Font::GetName(int handle, MonoString* name) {
		UNIMPLEMENTED();
	}
	int Font::GetSize(int handle, int* size) {
		UNIMPLEMENTED();
	}
	int Font::GetStyle(int handle, FontStyle* style) {
		UNIMPLEMENTED();
	}
	int Font::GetMetrics(int handle, FontMetrics* fontMetrics) {
		UNIMPLEMENTED();
	}
	int Font::GetTextWidthNative(int handle, MonoString* text, int offset, int len, int* width) {
		UNIMPLEMENTED();
	}
	int Font::GetTextMetricsNative(int handle, MonoString* text, int offset, int len, CharMetrics* charMetrics) {
		UNIMPLEMENTED();
	}
}
