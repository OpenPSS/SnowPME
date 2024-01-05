#ifndef LIB_PSS_TEXTINPUTMODE_H
#define LIB_PSS_TEXTINPUTMODE_H

namespace Sce::Pss::Core::Environment {
	enum class TextInputMode : unsigned int {
		Normal = 0,
		BasicLatin = 1,
		Password = 2
	};
}

#endif