#include <Debug/Logger.hpp>
#include <String/StringUtil.hpp>
#include <iostream>
#include <vector>

namespace Shared::Debug
{
	void Logger::logMultiline(std::string channel, std::string msg) {
		std::string fixedStr = String::StringUtil::Replace(msg, "\r", "");
		std::vector<std::string> lines = String::StringUtil::Split(fixedStr, "\n");

		for (std::string line : lines) {
			line = String::StringUtil::Replace(line, "\n", "");

			if (line.empty()) continue;

			if (channel != "ERROR" && channel != "WARN")
				std::cout << "[" << channel << "] " << line << std::endl;
			else
				std::cerr << "[" << channel << "] " << line << std::endl;
		}

	}

	void Logger::Debug(std::string msg) {
#ifdef _DEBUG
		logMultiline("DEBUG", msg);
#endif
	}
	void Logger::Warn(std::string msg) {
		logMultiline("WARN", msg);
	}
	void Logger::Error(std::string msg) {
		logMultiline("ERROR", msg);
	}
	void Logger::Info(std::string msg) {
		logMultiline("INFO", msg);
	}
	void Logger::Game(std::string msg) {
		logMultiline("GAME", msg);
	}
}
