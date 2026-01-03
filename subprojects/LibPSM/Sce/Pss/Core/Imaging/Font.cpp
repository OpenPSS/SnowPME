#include <Sce/Pss/Core/Imaging/Font.hpp>
#include <Sce/Pss/Core/Imaging/Impl/FontImpl.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <string>
#include <cstring>

using namespace Sce::Pss::Core::Imaging::Impl;
using namespace Sce::Pss::Core::System;

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
			this->fontImpl = std::make_unique<FontImpl>(fontName, filenames, size, style);
			PASS_ERRORABLE_SMARTPTR(this->fontImpl);
		}

	}

	FontStyle Font::Style() {
		FontStyle style = FontStyle::Regular;
		assert(this->fontImpl != nullptr);
		
		this->fontImpl->GetStyle(style);
		return style;
	}


	int Font::Size() {
		size_t size = 0;
		assert(this->fontImpl != nullptr);

		this->fontImpl->GetSize(&size);
		return static_cast<int>(size);
	}
	
	
	FontMetrics Font::Metrics() {
		FontMetrics metrics = { 0 };
		assert(this->fontImpl != nullptr);
		
		this->fontImpl->GetMetrics(metrics);
		return metrics;
	}

	int Font::GetTextWidth(const std::wstring& text, int offset, int len, int* width) {
		if (offset < 0 || offset > text.length() || len < 0 || (offset + len) > text.length())
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

		if (this->fontImpl != nullptr) {
			// get formatted text
			std::wstring fmtText = text.substr(offset, len);
			
			// calculate the width of the string in pixels.
			return this->fontImpl->GetCharSize(fmtText, width);
		}
		return PSM_ERROR_FONT_SYSTEM;
	}

	int Font::GetTextMetrics(const std::wstring& text, int offset, int len, CharMetrics* charMetrics) {
		if (offset < 0 || offset > text.length() || len < 0 || offset + len > text.length())
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

		if (this->fontImpl != nullptr) {
			// get formatted text
			std::wstring fmtText = text.substr(offset, len);

			// calculate the width of the string in pixels.
			return this->fontImpl->GetCharMetrics(fmtText, charMetrics);
		}
		return PSM_ERROR_FONT_SYSTEM;
		UNIMPLEMENTED();
	}


	int Font::NewFromFilenameSizeStyle(MonoString* filename, int size, FontStyle style, int* handle) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		const char* cfontname = mono_string_to_utf8(filename);
		const std::string fname = std::string(cfontname);

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
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Handles<Font>::IsValid(handle))
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		
		if (Handles<Font>::Get(handle)->fontImpl != nullptr) {
			const std::string sFontName = Handles<Font>::Get(handle)->fontImpl->Name();

			MonoString* msFontName = mono_string_new_wrapper(sFontName.c_str());
			mono_gc_wbarrier_generic_store(name, reinterpret_cast<MonoObject*>(msFontName));

			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_COMMON_OBJECT_DISPOSED;
	}
	int Font::GetSize(int handle, int* size) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Handles<Font>::IsValid(handle))
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		*size = Handles<Font>::Get(handle)->Size();
		return PSM_ERROR_NO_ERROR;
	}
	int Font::GetStyle(int handle, FontStyle* style) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Handles<Font>::IsValid(handle))
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		*style = Handles<Font>::Get(handle)->Style();
		return PSM_ERROR_NO_ERROR;
	}
	int Font::GetMetrics(int handle, FontMetrics* fontMetrics) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Handles<Font>::IsValid(handle))
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		*fontMetrics = Handles<Font>::Get(handle)->Metrics();
		return PSM_ERROR_NO_ERROR;
	}

	int Font::GetTextWidthNative(int handle, MonoString* text, int offset, int len, int* width) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Handles<Font>::IsValid(handle))
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		if (text == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		// get text
		wchar_t* chkTxt = reinterpret_cast<wchar_t*>(mono_string_chars(text));
		int chkLen = mono_string_length(text);

		const std::wstring textForCalc(chkTxt, chkLen);
		return Handles<Font>::Get(handle)->GetTextWidth(textForCalc, offset, len, width);
	}
	int Font::GetTextMetricsNative(int handle, MonoString* text, int offset, int len, MonoArray* charMetrics) {
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();

		if (!Handles<Font>::IsValid(handle))
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		if (text == nullptr) 
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		// get text
		wchar_t* chkTxt = reinterpret_cast<wchar_t*>(mono_string_chars(text));
		int chkLen = mono_string_length(text);
		const std::wstring textForCalc(chkTxt, chkLen);

		// get metrics
		CharMetrics* metrics = reinterpret_cast<CharMetrics*>(mono_array_addr_with_size(charMetrics, sizeof(CharMetrics), 0));

		return Handles<Font>::Get(handle)->GetTextMetrics(textForCalc, offset, len, metrics);
	}
}
