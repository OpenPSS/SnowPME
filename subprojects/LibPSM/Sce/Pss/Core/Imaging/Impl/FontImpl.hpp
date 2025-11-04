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
		
		uint8_t* ttfFileBuffer = nullptr;
		size_t ttfFileSize = 0;

		stbtt_fontinfo font;
		int lookupAndLoadFile(const std::string& ttfFilepath);
		int loadFontFile(const std::string& ttfFilepath);
		int loadFontMemory(const uint8_t* ttfBuffer, const size_t ttfSize);
	public:

		FontImpl(const std::string& fontName, const FontFileNames& filenames, int size, FontStyle style);
		static FontFileNames* Find(const std::string& name, int size, FontStyle style);
	};
};
#endif