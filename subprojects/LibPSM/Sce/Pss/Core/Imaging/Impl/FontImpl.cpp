#include <string>
#include <filesystem>
#include <fstream>

#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Imaging/Impl/FontImpl.hpp>
#include <Sce/Pss/Core/Imaging/FontStyle.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>

#define STB_TRUETYPE_IMPLEMENTATION 1
#include <stb/stb_truetype.h>

using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Imaging;

namespace Sce::Pss::Core::Imaging::Impl {
	std::unordered_map<std::string, FontFileNames> FontImpl::entries;

	int FontImpl::lookupAndLoadFile(const std::string& ttfFilepath) {
		if (ttfFilepath.starts_with("embed:")) {
			Logger::Todo("Trying to load embeded font. not yet supported.");
			return PSM_ERROR_NOT_IMPLEMENTED;
		}
		else {
			return this->loadFontFile(ttfFilepath);
		}
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

	FontImpl::FontImpl(const std::string& fontName, const FontFileNames& filenames, int size, FontStyle style) {
		entries.emplace(fontName, filenames);
		this->files = filenames;

		if (lookupAndLoadFile(filenames.fontFile1) == PSM_ERROR_NO_ERROR) {
			stbtt_InitFont(&this->font, this->ttfFileBuffer, stbtt_GetFontOffsetForIndex(this->ttfFileBuffer, 0));
		}
		
	}

	FontFileNames* FontImpl::Find(const std::string& name, int size, FontStyle style) {
		if (entries.contains(name)) {
			return &entries[name];
		}
		return nullptr;
	}
};
