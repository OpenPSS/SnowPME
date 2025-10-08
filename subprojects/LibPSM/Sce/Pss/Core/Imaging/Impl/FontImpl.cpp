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

	void FontImpl::lookupAndLoadFile(const std::string& ttfFilepath) {
		if (ttfFilepath.starts_with("embed:")) {
			Logger::Error("Trying to load embeded font. not yet supported.");
			return;
		}
		else {
			this->loadFontFile(ttfFilepath);
		}
	}
	void FontImpl::loadFontFile(const std::string& ttfFilePath) {
		// read ttf file
		std::fstream ttf(ttfFilePath, std::ios::binary | std::ios::in);
		ttf.read(reinterpret_cast<char*>(this->ttfFileBuffer), this->ttfFileSize);
		ttf.close();
	}

	FontImpl::FontImpl(const std::string& fontName, const FontFileNames& filenames, int size, FontStyle style) {
		entries.emplace(fontName, filenames);
		this->files = filenames;

		// get ttf size
		this->ttfFileSize = std::filesystem::file_size(this->files.fontFile1);
		this->ttfFileBuffer = reinterpret_cast<uint8_t*>(HeapAllocator::UniqueObject()->sce_psm_malloc(this->ttfFileSize));

		if (files.fontFile1.starts_with("embed:")) {
			loadFontFile(this->files.fontFile1);

		}


		stbtt_InitFont(&this->font, this->ttfFileBuffer, stbtt_GetFontOffsetForIndex(this->ttfFileBuffer, 0));
	}

	FontFileNames* FontImpl::Find(const std::string& name, int size, FontStyle style) {
		if (entries.contains(name)) {
			return &entries[name];
		}
		return nullptr;
	}
};
