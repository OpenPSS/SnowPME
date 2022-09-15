#ifndef LIB_PSM_TEXTINPUTMODE_H
#define LIB_PSM_TEXTINPUTMODE_H

namespace Sce::PlayStation::Core::Environment {
	enum class TextInputMode : unsigned int {
		Normal = 0,
		BasicLatin = 1,
		Password = 2
	};
}

#endif