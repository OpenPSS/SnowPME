#ifndef SNOW_PME_LOGGER_H
#define SNOW_PME_LOGGER_H 1
#include <string>
namespace SnowPME::Debug
{
	class Logger {
	public:
		static void Debug(std::string msg);
		static void Error(std::string msg);
		static void Warn(std::string msg);
		static void Info(std::string msg);

	};
}

#endif