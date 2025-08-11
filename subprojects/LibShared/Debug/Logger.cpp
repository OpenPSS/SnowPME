#include <Debug/ConsoleColor.hpp>
#include <Debug/Logger.hpp>
#include <Config.hpp>
#include <String/Format.hpp>
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

	inline void Logger::changeColor(ConsoleColor color) {
		std::scoped_lock<std::mutex> lock(Logger::colorMutex);
#if defined(_WIN32)
		HANDLE hConsole = GetStdHandle(STD_ERROR_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
#elif defined(__linux__) || defined(__APPLE__)

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
#warning do not know how to do colored text on this platform.
#endif
	}


	void inline Logger::logMultiline(const std::string& channel, const std::string& msg, std::ostream& stream) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
		std::string fixedStr = Format::Replace(msg, "\r", "");
		std::vector<std::string> lines = Format::Split(fixedStr, "\n");

		for (std::string line : lines) {
			line = Format::Replace(line, "\n", "");
			if (line.empty()) continue;

			std::cerr << "[" << channel << "] ";
			stream <<  line << std::endl;

		}

		changeColor(ConsoleColor::White);
	}

	inline std::string Logger::createHexString(const void* buffer, size_t size) {
		std::string msg = "";
		for (size_t i = 0; i < size; i++) {
			msg += Format::ZFill(Format::Hex(reinterpret_cast<const uint8_t*>(buffer)[i]), '0', 2);
		}
		return msg;
	}

	void Logger::Debug(const std::string& msg) {
		if (!Config::DebugLogging) return;
		changeColor(ConsoleColor::Gray);
		logMultiline("DEBUG", msg, std::cerr);
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

	void Logger::Debug(const void* buffer, size_t size) {
		if (!Config::DebugLogging) return;
		Logger::Debug(createHexString(buffer, size));
	}
	void Logger::Error(const void* buffer, size_t size) {
		Logger::Error(createHexString(buffer, size));
	}
	void Logger::Todo(const void* buffer, size_t size) {
		Logger::Todo(createHexString(buffer, size));
	}
	void Logger::Warn(const void* buffer, size_t size) {
		Logger::Warn(createHexString(buffer, size));
	}
	void Logger::Info(const void* buffer, size_t size) {
		Logger::Info(createHexString(buffer, size));
	}
	void Logger::Game(const void* buffer, size_t size) {
		Logger::Game(createHexString(buffer, size));
	}

}
