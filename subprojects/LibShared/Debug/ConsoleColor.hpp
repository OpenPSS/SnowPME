#ifndef SHARED_CONSOLECOLOR_H
#define SHARED_CONSOLECOLOR_H 1


namespace Shared::Debug {
	enum class ConsoleColor : int {
		Black = 0x0,
		Blue = 0x1,
		Green = 0x2,
		Aqua = 0x3,
		Red = 0x4,
		Purple = 0x5,
		Yellow = 0x6,
		White = 0x7,
		Gray = 0x8,
		LightBlue = 0x9,
		LightGreen = 0xA,
		LightAqua = 0xB,
		LightRed = 0xC,
		LightYellow = 0xE,
		LightWhite = 0xF
	};
}
#endif