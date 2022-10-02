#include <Util/Config.hpp>
#include <IO/Path.hpp>
using namespace SnowPME::IO;
namespace SnowPME::Util
{
	
	bool Config::SecurityCritical = false; 
	std::string Config::RuntimeLibPath = Path::Combine(RUNTIME_FOLDER, "lib");
	std::string Config::RuntimeConfigPath = Path::Combine(RUNTIME_FOLDER, "etc");
	std::string Config::RuntimeMonoPath = Path::Combine(RuntimeLibPath, "mono");
	std::string Config::RuntimeVerisonPath = Path::Combine(RuntimeMonoPath, "2.1");
	std::string Config::PsmLibsPath = Path::Combine(RuntimeLibPath, "psm");

	std::string Config::PsmCoreLibPath = Path::Combine(PsmLibsPath, "Sce.PlayStation.Core.dll");
	std::string Config::SystemLibPath = Path::Combine(RuntimeVerisonPath, "System.dll");
	std::string Config::MscorlibPath = Path::Combine(RuntimeVerisonPath, "mscorlib.dll");

	int Config::ReadConfig(std::string configFile) {
		// TODO Actually read the file
		return 0;
	}
}