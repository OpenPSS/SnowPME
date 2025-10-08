#ifndef LIB_PSS_IMPL_FONT_H
#define LIB_PSS_IMPL_FONT_H 1

#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Imaging/Impl/FontFileNames.hpp>
#include <Sce/Pss/Core/Imaging/FontStyle.hpp>
#include <string>
#include <unordered_map>
#include <stb/stb_truetype.h>

namespace Sce::Pss::Core::Imaging::Impl {
	class FontImpl : public Errorable {
	private:
		static std::unordered_map<std::string, FontFileNames> entries;
		FontFileNames files;
		
		uint8_t* ttfFileBuffer;
		size_t ttfFileSize;

		stbtt_fontinfo font;
		void lookupAndLoadFile(const std::string& ttfFilepath);
		void loadFontFile(const std::string& ttfFilepath);
	public:

		FontImpl(const std::string& fontName, const FontFileNames& filenames, int size, FontStyle style);
		static FontFileNames* Find(const std::string& name, int size, FontStyle style);
	};
};
#endif