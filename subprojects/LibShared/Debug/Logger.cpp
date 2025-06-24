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
		WORD attribute = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

		WORD FOREGROUND_GOLD = FOREGROUND_RED | FOREGROUND_GREEN;
		WORD FOREGROUND_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		WORD FOREGROUND_GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		WORD FOREGROUND_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

		WORD FOREGROUND_LGREEN =  FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		WORD FOREGROUND_LRED = FOREGROUND_RED | FOREGROUND_INTENSITY;
		WORD FOREGROUND_LBLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;

		// Set text color
		switch (color) {
		case ConsoleColor::Red:
			attribute = FOREGROUND_RED;
			break;
		case ConsoleColor::Green:
			attribute = FOREGROUND_GREEN;
			break;
		case ConsoleColor::Blue:
			attribute = FOREGROUND_BLUE;
			break;
		case ConsoleColor::Yellow:
			attribute = FOREGROUND_YELLOW;
			break;
		case ConsoleColor::Gray:
			attribute = FOREGROUND_GRAY;
			break;
		case ConsoleColor::White:
			attribute = FOREGROUND_WHITE;
			break;
		case ConsoleColor::Gold:
			attribute = FOREGROUND_GOLD;
			break;
		case ConsoleColor::LightGreen:
			attribute = FOREGROUND_LGREEN;
			break;
		case ConsoleColor::LightRed:
			attribute = FOREGROUND_LRED;
			break;
		case ConsoleColor::LightBlue:
			attribute = FOREGROUND_LBLUE;
			break;
		default:
			attribute = FOREGROUND_GRAY;
			break;
		};

		SetConsoleTextAttribute(hConsole, attribute);
#elif __linux__

		/*
		\e[0;30m or \e[0;90m: Black
		\e[0;31m or \e[0;91m: Red
		\e[0;32m or \e[0;92m: Green
		\e[0;33m or \e[0;93m: Yellow
		\e[0;34m or \e[0;94m: Blue
		\e[0;35m or \e[0;95m: Magenta
		\e[0;36m or \e[0;96m: Cyan
		\e[0;37m or \e[0;97m: White
		*/

		std::string FOREGROUND_RESET = "\e[0m";
		std::string FOREGROUND_RED = "\e[31m";
		std::string FOREGROUND_BLUE = "\e[34m";
		std::string FOREGROUND_GREEN = "\e[32m";

		std::string FOREGROUND_GOLD = "\e[33m";
		std::string FOREGROUND_YELLOW = "\e[93m";
		std::string FOREGROUND_GRAY = "\e[37m";
		std::string FOREGROUND_WHITE = "\e[97m";

		std::string FOREGROUND_LGREEN = "\e[92m";
		std::string FOREGROUND_LRED = "\e[91m";
		std::string FOREGROUND_LBLUE = "\e[94m";


		std::cerr << FOREGROUND_RESET;

		switch (color) {
		case ConsoleColor::Red:
			std::cerr << FOREGROUND_RED;
			break;
		case ConsoleColor::Green:
			std::cerr << FOREGROUND_GREEN;
			break;
		case ConsoleColor::Blue:
			std::cerr << FOREGROUND_BLUE;
			break;
		case ConsoleColor::Yellow:
			std::cerr << FOREGROUND_YELLOW;
			break;
		case ConsoleColor::Gray:
			std::cerr << FOREGROUND_GREY
			break;
		case ConsoleColor::White:
			std::cerr << FOREGROUND_WHITE;
			break;
		case ConsoleColor::LightGreen:
			std::cerr << FOREGROUND_LGREEN;
			break;
		case ConsoleColor::LightRed:
			std::cerr << FOREGROUND_LRED;
			break;
		default:
			std::cerr << FOREGROUND_GREY;
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

		changeColor(ConsoleColor::Gray);
	}

	void Logger::Debug(const std::string& msg) {
#ifdef _DEBUG
		changeColor(ConsoleColor::Blue);
		logMultiline("DEBUG", msg, std::cerr);
#endif
	}
	void Logger::Todo(const std::string& msg) {
		changeColor(ConsoleColor::LightRed);
		logMultiline("TODO", msg, std::cerr);
	}

	void Logger::Warn(const std::string& msg) {
		changeColor(ConsoleColor::Yellow);
		logMultiline("WARN", msg, std::cerr);
	}

	void Logger::Error(const std::string& msg) {
		changeColor(ConsoleColor::Red);
		logMultiline("ERROR", msg, std::cerr);
	}

	void Logger::Info(const std::string& msg) {
		changeColor(ConsoleColor::LightGreen);
		logMultiline("INFO", msg, std::cerr);
	}

	void Logger::Game(const std::string& msg) {
		changeColor(ConsoleColor::White);
		logMultiline("GAME", msg, std::cout);
	}

}
