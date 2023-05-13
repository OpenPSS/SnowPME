#ifndef SHARED_LOGGER_H
#define SHARED_LOGGER_H 1
#include <string>
namespace Shared::Debug
{
	class Logger {
	private:
		static void logMultiline(std::string channel, std::string msg);
	public:
		static void Debug(std::string msg);
		static void Error(std::string msg);
		static void Warn(std::string msg);
		static void Info(std::string msg);
		static void Game(std::string msg);

	};
}

#endif