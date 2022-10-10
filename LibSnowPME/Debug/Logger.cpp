#include <Debug/Logger.hpp>
#include <Util/StringUtils.hpp>
#include <iostream>
using namespace SnowPME::Util;

namespace SnowPME::Debug
{
	void Logger::logMultiline(std::string channel, std::string msg) {
		std::string fixedStr = StringUtils::Replace(msg, "\r", "");
		std::vector<std::string> lines = StringUtils::Split(fixedStr, "\n");

		for (std::string line : lines) {
			line = StringUtils::Replace(line, "\n", "");
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
