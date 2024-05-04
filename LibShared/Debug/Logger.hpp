#ifndef SHARED_LOGGER_H
#define SHARED_LOGGER_H 1
#include <string>

namespace Shared::Debug
{
	class Logger {
	private:
		static void logMultiline(const std::string& channel, const std::string& msg);
	public:
		static void Debug(const std::string& msg);
		static void Error(const std::string& msg);
		static void Warn(const std::string& msg);
		static void Info(const std::string& msg);
		static void Game(const std::string& msg);

	};
}

#endif