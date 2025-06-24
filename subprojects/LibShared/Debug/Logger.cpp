#include <Debug/ConsoleColor.hpp>
#include <Debug/Logger.hpp>
#include <String/StringUtil.hpp>
#include <iostream>
#include <vector>
#include <mutex>

using namespace Shared::String;
namespace Shared::Debug
{
	std::mutex Logger::logMutex;

	void inline Logger::changeColor(ConsoleColor color) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD attribute = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

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
			attribute = FOREGROUND_RED | FOREGROUND_GREEN;
			break;
		case ConsoleColor::Gray:
			attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		case ConsoleColor::White:
			attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
			break;
		};

		SetConsoleTextAttribute(hConsole, attribute);
#elif __linux__
		std::string FOREGROUND_RESET = "\033[0m";
		std::string FOREGROUND_RED = "\033[31m";
		std::string FOREGROUND_GREEN = "\033[32m";
		std::string FOREGROUND_BLUE = "\033[34m";

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
			std::cerr << FOREGROUND_RED << FOREGROUND_GREEN;
			break;
		case ConsoleColor::Gray:
			std::cerr << FOREGROUND_RED << FOREGROUND_GREEN << FOREGROUND_BLUE;
			break;
		case ConsoleColor::White:
			std::cerr << FOREGROUND_RED << FOREGROUND_GREEN << FOREGROUND_BLUE;
			break;
		};


#else
		#warn cannot do colored text on this platform.
#endif
	}

	void inline Logger::logMultiline(const std::string& channel, const std::string& msg) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
		std::string fixedStr = StringUtil::Replace(msg, "\r", "");
		std::vector<std::string> lines = StringUtil::Split(fixedStr, "\n");

		for (std::string line : lines) {
			line = StringUtil::Replace(line, "\n", "");
			if (line.empty()) continue;

			std::cerr << "[" << channel << "] ";
			if (channel == "GAME")
				std::cout <<  line << std::endl;
			else 
				std::cerr << line << std::endl;

		}

	}

	void Logger::Debug(const std::string& msg) {
#ifdef _DEBUG
		changeColor(ConsoleColor::Gray);
		logMultiline("DEBUG", msg);
#endif
	}
	void Logger::Todo(const std::string& msg) {
		changeColor(ConsoleColor::Red);
		logMultiline("TODO", msg);
	}

	void Logger::Warn(const std::string& msg) {
		changeColor(ConsoleColor::Yellow);
		logMultiline("WARN", msg);
	}

	void Logger::Error(const std::string& msg) {
		changeColor(ConsoleColor::Red);
		logMultiline("ERROR", msg);
	}

	void Logger::Info(const std::string& msg) {
		changeColor(ConsoleColor::Blue);
		logMultiline("INFO", msg);
	}

	void Logger::Game(const std::string& msg) {
		changeColor(ConsoleColor::White);
		logMultiline("GAME", msg);
	}

}
