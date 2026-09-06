#include <string>
#include <filesystem>
#include <fstream>

#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Imaging/Impl/FontImpl.hpp>
#include <Sce/Pss/Core/Imaging/FontStyle.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Imaging/FontMetrics.hpp>
#include <Sce/Pss/Core/Imaging/CharMetrics.hpp>
#include <Sce/Pss/Core/Imaging/Impl/EmbeddedFonts.h>

#include <SDL3_ttf/SDL_ttf.h>
#include <LibShared.hpp>

#include <locale>
#include <codecvt>

using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Imaging;
using namespace Shared;

namespace Sce::Pss::Core::Imaging::Impl {
	std::unordered_map<std::string, FontFileNames> FontImpl::entries;
	bool FontImpl::isInitalized = false;

	void FontImpl::initFonts() {
		if (!FontImpl::isInitalized) {
			TTF_Init();
			FontImpl::isInitalized = true;
		}
	}

	int FontImpl::lookupAndLoadFile(const std::string& ttfFilepath) {
		if (ttfFilepath.starts_with("embed:")) {
			std::string embedFont = ttfFilepath.substr(6);
			std::string fontPath = std::filesystem::path(Config::GetRuntimeConfigFolder()).append("font").append(embedFont).string();
			if (std::filesystem::exists(fontPath)) {
				return this->loadFontFile(fontPath);
			}
			else {
				return loadFontMemory(font_default_data, font_default_size);
			}
		}
		else {
			return this->loadFontFile(ttfFilepath);
		}
	}
	int FontImpl::loadFontMemory(const uint8_t* ttfBuffer, const size_t ttfSize) {
		this->ttfFileSize = ttfSize;
		this->ttfFileBuffer = reinterpret_cast<uint8_t*>(HeapAllocator::UniqueObject()->sce_psm_malloc(this->ttfFileSize));
		memcpy(this->ttfFileBuffer, reinterpret_cast<const void*>(ttfBuffer), this->ttfFileSize);

		return PSM_ERROR_NO_ERROR;
	}

	int FontImpl::loadFontFile(const std::string& ttfFilePath) {
		// read ttf file
		std::error_code ec;
		this->ttfFileSize = std::filesystem::file_size(this->files.fontFile1, ec);
		if (ec) {
			this->ttfFileBuffer = reinterpret_cast<uint8_t*>(HeapAllocator::UniqueObject()->sce_psm_malloc(this->ttfFileSize));

			std::fstream ttf(ttfFilePath, std::ios::binary | std::ios::in);
			ttf.read(reinterpret_cast<char*>(this->ttfFileBuffer), this->ttfFileSize);
			ttf.close();
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_FILE_NOT_FOUND;
	}

	const std::string FontImpl::Name() {
		return this->name;
	}

	FontImpl::FontImpl(const std::string& fontName, const FontFileNames& filenames, int size, FontStyle style) {
		initFonts();
		
		entries.emplace(fontName, filenames);
		this->files = filenames;
		this->fontSize = size;
		this->name = fontName;

		if (lookupAndLoadFile(filenames.fontFile1) == PSM_ERROR_NO_ERROR) {
			SDL_IOStream* ops = SDL_IOFromConstMem(ttfFileBuffer, ttfFileSize);
			if (ops == nullptr) this->SetError(PSM_ERROR_FONT_SYSTEM);

			this->font = TTF_OpenFontIO(ops, 1, this->fontSize);
			if (this->font == nullptr) this->SetError(PSM_ERROR_FONT_SYSTEM);
		}
		
	}

	FontImpl::~FontImpl() {
		if (this->font != nullptr) {
			TTF_CloseFont(this->font);
		}
	}

	int FontImpl::GetSize(size_t* size) {
		if (size != nullptr && this->font != nullptr) {
			*size = this->fontSize;
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_FONT_SYSTEM;
	}


	int FontImpl::GetCharSize(std::u16string& text, int* width) {
		if (this->font != nullptr) {
			
			std::u8string txt = String::Encoding::Utf16ToUtf8(text);
			if (TTF_MeasureString(this->font, (const char*)txt.c_str(), txt.length(), Config::ScreenWidth(0), width, nullptr) == true) {
				return PSM_ERROR_NO_ERROR;
			}
			else {
				return PSM_ERROR_FONT_SYSTEM;
			}
		}
		return PSM_ERROR_FONT_SYSTEM;
	}



	int FontImpl::GetCharMetrics(std::u16string& text, CharMetrics* metrics) {
		if (this->font != nullptr) {
			Logger::Warn("Font Glyph Metrics are not completely accurate yet!!");
			int x, width, y, height, advance = 0;


			for (size_t i = 0; i < text.length(); i++) {
				char16_t chr = text[i];

				// TODO: 
				// PSM returns floats for all of these values
				// and has two extra values in Metrics (HorizontalBaring values) 
				// which is not implemented correctly.

				if (TTF_GetGlyphMetrics(this->font, static_cast<uint32_t>(chr), &x, &width, &y, &height, &advance) == true) {
					memset(&metrics[i], 0, sizeof(CharMetrics));
					

					// copy it over ...
					metrics[i].X = static_cast<float>(x);
					metrics[i].Width = static_cast<float>(width);
					metrics[i].Y = static_cast<float>(y);
					metrics[i].Height = static_cast<float>(height);
					metrics[i].HorizontalAdvance = static_cast<float>(advance);

				}
				else {
					return PSM_ERROR_FONT_SYSTEM;
				}
			}
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_FONT_SYSTEM;
	}

	int FontImpl::GetMetrics(FontMetrics& metrics) {
		if (this->font != nullptr) {
			metrics.Ascent = TTF_GetFontAscent(this->font);
			metrics.Descent = TTF_GetFontDescent(this->font);
			metrics.Leading = TTF_GetFontLineSkip(this->font);
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_FONT_SYSTEM;

	}

	int FontImpl::GetStyle(FontStyle& style) {
		if (this->font != nullptr) {
			int s = TTF_GetFontStyle(this->font);

			if ((s & TTF_STYLE_BOLD) != 0) {
				style |= FontStyle::Bold;
			}
			if ((s & TTF_STYLE_ITALIC) != 0) {
				style |= FontStyle::Italic;
			}
			if ((s & TTF_STYLE_NORMAL) != 0) {
				style |= FontStyle::Regular;
			}
		}
		return PSM_ERROR_FONT_SYSTEM;
	}

	FontFileNames* FontImpl::Find(const std::string& name, int size, FontStyle style) {
		if (entries.contains(name)) {
			return &entries[name];
		}
		return nullptr;
	}
};
