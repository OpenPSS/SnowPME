#ifndef LIB_PSS_IMPL_FONT_FILENAMES_H
#define LIB_PSS_IMPL_FONT_FILENAMES_H 1
#include <cstdint>
namespace Sce::Pss::Core::Imaging::Impl {
	typedef struct FontFileNames {
		std::string fontFile1 = "";
		std::string fontFile2 = "";
	} FontFileNames;
}
#endif