#ifndef SHARED_LOGGER_H
#define SHARED_LOGGER_H 1
#include <string>
#include <mutex>
#include <iostream>

#include <Debug/ConsoleColor.hpp>
namespace Shared::Debug
{
	class Logger {
	private:
		static std::mutex logMutex;
		static std::mutex colorMutex;
		static void logMultiline(const std::string& channel, const std::string& msg, std::ostream& stream);
		static void changeColor(ConsoleColor color);
	public:
		static void Debug(const std::string& msg);
		static void Error(const std::string& msg);
		static void Todo(const std::string& msg);
		static void Warn(const std::string& msg);
		static void Info(const std::string& msg);
		static void Game(const std::string& msg);
	};
}

#endif