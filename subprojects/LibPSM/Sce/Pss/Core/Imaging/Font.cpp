#include <Sce/Pss/Core/Imaging/Font.hpp>
#include <Sce/Pss/Core/Imaging/Impl/FontImpl.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <string.h>

using namespace Sce::Pss::Core::Imaging::Impl;

namespace Sce::Pss::Core::Imaging {
	Font::Font(const std::string& filename, int size, FontStyle style) {
		FontImpl::Find(filename, size, style);
		UNIMPLEMENTED_ERRORABLE("creating font from filename not implemented.");
	}

	Font::Font(FontAlias alias, int size, FontStyle style) {
		std::string fontName = "__System__";
		FontFileNames filenames = {
			.fontFile1 = "embed:ltn0.pvf",
			.fontFile2 = "embed:jpn0.pvf"
		};

		FontFileNames* fnames = FontImpl::Find(fontName, size, style);

		if (fnames == nullptr) {
			this->fontImpl = std::make_shared<FontImpl>(fontName, filenames, size, style);
		}

		UNIMPLEMENTED_ERRORABLE("creating font from filealias not implemented.");
	}

	int Font::NewFromFilenameSizeStyle(MonoString* filename, int size, FontStyle style, int* handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		const char* cfontname = mono_string_to_utf8(filename);
		std::string fname = std::string(cfontname);

		std::shared_ptr<Font> fnt = Font::Create(fname, size, style);
		RETURN_ERRORABLE_PSMOBJECT(fnt, Font);

		*handle = fnt->Handle();
		return PSM_ERROR_NO_ERROR;
	}
	int Font::NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int* handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();
		
		std::shared_ptr<Font> fnt = Font::Create(alias, size, style);
		RETURN_ERRORABLE_PSMOBJECT(fnt, Font);

		*handle = fnt->Handle();
		return PSM_ERROR_NO_ERROR;
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
