#ifndef SHARED_CONSOLECOLOR_H
#define SHARED_CONSOLECOLOR_H 1

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

namespace Shared::Debug {
	enum class ConsoleColor : int {
		Red,
		Green,
		Blue,
		Yellow,
		Gray,
		White
	};
}
#endif