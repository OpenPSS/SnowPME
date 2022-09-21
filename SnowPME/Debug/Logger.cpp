#include <Debug/Logger.hpp>
#include <iostream>
namespace SnowPME::Debug
{
	void Logger::Debug(std::string msg) {
#ifdef _DEBUG
		std::cout << "[DEBUG] " << msg << std::endl;
#endif
	}
	void Logger::Error(std::string msg) {
		std::cerr << "[ERROR] " << msg << std::endl;
	}
	void Logger::Info(std::string msg) {
		std::cout << "[INFO] " << msg << std::endl;
	}
}
