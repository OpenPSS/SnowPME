#ifndef LIB_PSS_CLIPBOARD_H
#define LIB_PSS_CLIPBOARD_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::Pss::Core::Environment {
	class Clipboard {
	public:
		static int SetTextNative(std::string text);
		static int GetTextNative(std::string *text);
	};
}
#endif
