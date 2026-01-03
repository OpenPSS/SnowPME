#ifndef LIB_PSS_IMPL_FONT_H
#define LIB_PSS_IMPL_FONT_H 1

#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Imaging/Impl/FontFileNames.hpp>
#include <Sce/Pss/Core/Imaging/FontStyle.hpp>
#include <Sce/Pss/Core/Imaging/FontMetrics.hpp>
#include <string>
#include <unordered_map>

// using sdl font library
#include <SDL2/SDL_ttf.h>

namespace Sce::Pss::Core::Imaging::Impl {
	class FontImpl : public Errorable {
	private:
		static std::unordered_map<std::string, FontFileNames> entries;
		static bool isInitalized;

		FontFileNames files;
		
		uint8_t* ttfFileBuffer = nullptr;
		size_t ttfFileSize = 0;
		TTF_Font* font = nullptr;

		std::string name;

		void initFonts();

		int lookupAndLoadFile(const std::string& ttfFilepath);
		int loadFontFile(const std::string& ttfFilepath);
		int loadFontMemory(const uint8_t* ttfBuffer, const size_t ttfSize);
	public:
		std::string Name();

		int GetMetrics(Sce::Pss::Core::Imaging::FontMetrics* metrics);
		int GetStyle(Sce::Pss::Core::Imaging::FontStyle& style);
		int GetCharSize(std::wstring& text, int* width);

		FontImpl(const std::string& fontName, const FontFileNames& filenames, int size, FontStyle style);
		~FontImpl();
		static FontFileNames* Find(const std::string& name, int size, FontStyle style);
	};
};
#endif