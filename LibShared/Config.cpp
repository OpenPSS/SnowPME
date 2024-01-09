#include <Config.hpp>
#include <String/Path.hpp>
#include <fstream>
#include <string>

using namespace Shared::String;

namespace Shared
{
	static const std::string SEPERATOR = ":";
	static int screenWidth = 960;
	static int screenHeight = 544;
	std::string RuntimeFolder = "Runtime";
	bool Config::SecurityCritical = false;

	std::string Config::RuntimeLibPath = Path::Combine(RuntimeFolder, "lib");
	std::string Config::RuntimeConfigPath = Path::Combine(RuntimeFolder, "etc");
	std::string Config::RuntimeMonoPath = Path::Combine(RuntimeLibPath, "mono");
	std::string Config::RuntimeVerisonPath = Path::Combine(RuntimeMonoPath, "2.1");
	std::string Config::PsmLibsPath = Path::Combine(RuntimeLibPath, "psm");

	std::string Config::PsmCoreLibPath = Path::Combine(PsmLibsPath, "Sce.PlayStation.Core.dll");
	std::string Config::SystemLibPath = Path::Combine(RuntimeVerisonPath, "System.dll");
	std::string Config::MscorlibPath = Path::Combine(RuntimeVerisonPath, "mscorlib.dll");
	
	int Config::ScreenTotal = 1;
	std::string Config::Username = "Li";
	uint64_t Config::AccountId = 0x0000000000000000;
	RuntimeImplementation Config::TargetImplementation = RuntimeImplementation::PSVita;

	int Config::ScreenHeight(int idx) {
		return screenHeight;
	}

	int Config::ScreenWidth(int idx) {
		return screenWidth;
	}

	int Config::ReadConfig(std::string configFile) {
		std::ifstream cfgStream = std::ifstream(configFile);
		
		std::string ln;
		while (std::getline(cfgStream, ln)) {


		}

		return 0;
	}
}