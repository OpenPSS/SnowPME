#include <Util/Config.hpp>
namespace SnowPME::Util
{
	
	bool Config::SecurityCritical = false; 
	std::string Config::PsmCorelibsPath = PSM_CORELIB_PATH;
	std::string Config::RuntimeLibPath = RUNTIME_LIB_PATH;
	std::string Config::RuntimeConfigPath = RUNTIME_CONFIG_PATH;

	int Config::ReadConfig(std::string configFile) {
		// TODO Actually read the file
		return 0;
	}
}