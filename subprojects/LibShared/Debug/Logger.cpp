#include <Debug/Logger.hpp>
#include <String/StringUtil.hpp>
#include <iostream>
#include <vector>
#include <mutex>

namespace Shared::Debug
{
	std::mutex Logger::logMutex;
	void inline Logger::logMultiline(const std::string& channel, const std::string& msg) {
		
		std::string fixedStr = String::StringUtil::Replace(msg, "\r", "");
		std::vector<std::string> lines = String::StringUtil::Split(fixedStr, "\n");

		for (std::string& line : lines) {
			line = String::StringUtil::Replace(line, "\n", "");

			if (line.empty()) continue;

			if (channel != "ERROR" && channel != "WARN")
				std::cout << "[" << channel << "] " << line << std::endl;
			else
				std::cerr << "[" << channel << "] " << line << std::endl;
		}

	}

	void Logger::Debug(const std::string& msg) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
#ifdef _DEBUG
		logMultiline("DEBUG", msg);
#endif
	}
	void Logger::Warn(const std::string& msg) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
		logMultiline("WARN", msg);
	}
	void Logger::Error(const std::string& msg) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
		logMultiline("ERROR", msg);
	}
	void Logger::Info(const std::string& msg) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
		logMultiline("INFO", msg);
	}
	void Logger::Game(const std::string& msg) {
		std::scoped_lock<std::mutex> lock(Logger::logMutex);
		logMultiline("GAME", msg);
	}
}
