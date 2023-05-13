#include <Config.hpp>
#include <String/Path.hpp>

using namespace Shared::String;

namespace Shared
{
	static int screenWidth = 960;
	static int screenHeight = 544;
	static int screenTotal = 1;

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

	// TODO: Implement multiple screens (i have no idea what that would even be for tho? reartouch???)
	int Config::ScreenWidth(int idx) {
		return screenWidth;
	}

	RuntimeImplementation Config::GetRuntimeImplementation() {
		// for now windows version of runtime is only supported one.
		return RuntimeImplementation::Windows;
	}

	int Config::ScreenHeight(int idx) {
		return screenHeight;
	}

	int Config::ScreenTotal() {
		return screenTotal;
	}

	int Config::ReadConfig(std::string configFile) {
		// TODO Actually read the file
		return 0;
	}
}