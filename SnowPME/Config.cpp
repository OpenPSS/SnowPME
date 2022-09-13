#include "Config.hpp"
namespace SnowPME
{
	
	bool Config::SecurityCritical = false; 
	string Config::PsmCorelibsPath = PSM_CORELIB_PATH; 
	string Config::RuntimeLibPath = RUNTIME_LIB_PATH; 
	string Config::RuntimeConfigPath = RUNTIME_CONFIG_PATH; 

	int Config::ReadConfig(string configFile) {
		// TODO Actually read the file
		return 0;
	}
}