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
		inline static void logMultiline(const std::string& channel, const std::string& msg, std::ostream& stream);
		inline static void changeColor(ConsoleColor color);
		inline static std::string createHexString(const void* buffer, size_t size);
	public:
		static void Debug(const std::string& msg);
		static void Error(const std::string& msg);
		static void Todo(const std::string& msg);
		static void Warn(const std::string& msg);
		static void Info(const std::string& msg);
		static void Game(const std::string& msg);

		static void Debug(const void* buffer, size_t size);
		static void Error(const void* buffer, size_t size);
		static void Todo(const void* buffer, size_t size);
		static void Warn(const void* buffer, size_t size);
		static void Info(const void* buffer, size_t size);
		static void Game(const void* buffer, size_t size);
	};
}

#endif