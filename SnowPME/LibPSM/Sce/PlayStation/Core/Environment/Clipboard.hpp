#ifndef LIB_PSM_CLIPBOARD_H
#define LIB_PSM_CLIPBOARD_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {
	class Clipboard {
	public:
		static int SetTextNative(std::string text);
		static int GetTextNative(std::string *text);
	};
}
#endif
