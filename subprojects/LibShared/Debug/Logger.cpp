#include <Debug/ConsoleColor.hpp>
#include <Debug/Logger.hpp>
#include <String/StringUtil.hpp>
#include <iostream>
#include <vector>
#include <mutex>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

using namespace Shared::String;

namespace Shared::Debug
{
	std::mutex Logger::logMutex;
	std::mutex Logger::colorMutex;

	void inline Logger::changeColor(ConsoleColor color) {
		std::scoped_lock<std::mutex> lock(Logger::colorMutex);
#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
#elif __linux__

		std::string COLOR_RESET = "\e[0m";
		std::string COLOR_BLACK = "\e[30m";
		std::string COLOR_RED = "\e[31m";
		std::string COLOR_GREEN = "\e[32m";
		std::string COLOR_YELLOW = "\e[33m";
		std::string COLOR_BLUE = "\e[34m";
		std::string COLOR_MAGENTA = "\e[35m";
		std::string COLOR_CYAN = "\e[36m";
		std::string COLOR_WHITE = "\e[37m";

		std::string COLOR_GREY = "\e[90m";
		std::string COLOR_LRED = "\e[91m";
		std::string COLOR_LGREEN = "\e[92m";
		std::string COLOR_LYELLOW = "\e[93m";
		std::string COLOR_LBLUE = "\e[94m";
		std::string COLOR_LMAGENTA = "\e[95m";
		std::string COLOR_LCYAN = "\e[96m";
		std::string COLOR_LWHITE = "\e[97m";

		switch (color) {
		case ConsoleColor::Black:
			std::cerr << COLOR_BLACK;
			break;
		case ConsoleColor::Blue:
			std::cerr << COLOR_BLUE;
			break;
		case ConsoleColor::Green:
			std::cerr << COLOR_GREEN;
			break;
		case ConsoleColor::Aqua:
			std::cerr << COLOR_CYAN;
			break;
		case ConsoleColor::Red:
			std::cerr << COLOR_RED;
			break;
		case ConsoleColor::Purple:
			std::cerr << COLOR_MAGENTA;
			break;
		case ConsoleColor::Yellow:
			std::cerr << COLOR_YELLOW;
			break;
		case ConsoleColor::White:
			std::cerr << COLOR_WHITE;
			break;
		case ConsoleColor::Gray:
			std::cerr << COLOR_GREY;
			break;
		case ConsoleColor::LightBlue:
			std::cerr << COLOR_LBLUE;
			break;
		case ConsoleColor::LightGreen:
			std::cerr << COLOR_LGREEN;
			break;
		case ConsoleColor::LightAqua:
			std::cerr << COLOR_LCYAN;
			break;
		case ConsoleColor::LightRed:
			std::cerr << COLOR_LRED;
			break;
		case ConsoleColor::LightYellow:
			std::cerr << COLOR_LYELLOW;
			break;
		case ConsoleColor::LightWhite:
			std::cerr << COLOR_LWHITE;
			break;
		default:
			std::cerr << COLOR_WHITE;
			break;
		};


#else
		#warn cannot do colored text on this platform.
#endif
	}

	void inline Logger::logMultiline(const std::string& channel, const std::string& msg, std::ostream& stream) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
		std::string fixedStr = StringUtil::Replace(msg, "\r", "");
		std::vector<std::string> lines = StringUtil::Split(fixedStr, "\n");

		for (std::string line : lines) {
			line = StringUtil::Replace(line, "\n", "");
			if (line.empty()) continue;

			std::cout << "[" << channel << "] ";
			stream <<  line << std::endl;

		}

		changeColor(ConsoleColor::White);
	}

	void Logger::Debug(const std::string& msg) {
#ifdef _DEBUG
		changeColor(ConsoleColor::Gray);
		logMultiline("DEBUG", msg, std::cerr);
#endif
	}
	void Logger::Todo(const std::string& msg) {
		changeColor(ConsoleColor::Yellow);
		logMultiline("TODO", msg, std::cerr);
	}

	void Logger::Warn(const std::string& msg) {
		changeColor(ConsoleColor::LightYellow);
		logMultiline("WARN", msg, std::cerr);
	}

	void Logger::Error(const std::string& msg) {
		changeColor(ConsoleColor::LightRed);
		logMultiline("ERROR", msg, std::cerr);
	}

	void Logger::Info(const std::string& msg) {
		changeColor(ConsoleColor::LightBlue);
		logMultiline("INFO", msg, std::cerr);
	}

	void Logger::Game(const std::string& msg) {
		changeColor(ConsoleColor::LightWhite);
		logMultiline("GAME", msg, std::cout);
	}

}
