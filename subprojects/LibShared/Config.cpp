#include <Config.hpp>
#include <String/Path.hpp>
#include <String/StringUtil.hpp>
#include <Debug/Logger.hpp>
#include <fstream>
#include <string>
#include <cstring>

using namespace Shared::String;
using namespace Shared::Debug;

#define GET_CFG_KEY_STR(name) if (key == #name) strncpy(Config::name, value.c_str(), sizeof(Config::name)-1)
#define GET_CFG_KEY_UINT64(name) if (key == #name) Config::name = strtoull(value.c_str(), NULL, 16)
#define GET_CFG_KEY_ENUM(name, enumName) if (key == #name) Config::name = (enumName)strtoull(value.c_str(), NULL, 16)
#define GET_CFG_KEY_BOOL(name) if (key == #name) Config::name = (value == "true")

#define SET_CFG_COMMENT(str, cmt) str << COMMENT << cmt << std::endl;
#define SET_CFG_KEY_STR(str, name) str << #name << SEPERATOR << std::string(Config::name) << std::endl;
#define SET_CFG_KEY_UINT64(str, name) str << #name << SEPERATOR <<  std::hex << (uint64_t)Config::name << std::endl;
#define SET_CFG_KEY_ENUM(str, name) SET_CFG_KEY_UINT64(str, name)
#define SET_CFG_KEY_BOOL(str, name) str << #name << SEPERATOR <<  (Config::name ? "true" : "false") << std::endl;

namespace Shared
{

	static const std::string SEPERATOR = "=";
	static const std::string COMMENT = "#";

	static int screenWidth = 960;
	static int screenHeight = 544;

	std::string Config::RunningFromDirectory = "";
	std::string Config::cfgFilePath = "";

	int Config::ScreenTotal = 1;
	bool Config::SecurityCritical = false;

	char Config::RuntimeLibPath[0x1028] = "./dll";
	char Config::RuntimeConfigPath[0x1028] = "./dll";

	char Config::Username[0x1028] = "SnowPME";
	char Config::SystemLanguage[0x1028] = "en-US";

	uint64_t Config::AccountId = 0x123456789ABCDEF0ull;
	RuntimeImplementation Config::TargetImplementation = RuntimeImplementation::PSVita;

	bool Config::MonoDebugger = false;
	char Config::ProfilerSettings[0x1028] = "";

	char Config::PsmApps[0x1028] = "./psm";

	void Config::parseKeyValuePair(std::string key, std::string value) {
		GET_CFG_KEY_STR(Config::Username);
		GET_CFG_KEY_UINT64(Config::AccountId);

		GET_CFG_KEY_STR(Config::RuntimeLibPath);
		GET_CFG_KEY_STR(Config::RuntimeConfigPath);

		GET_CFG_KEY_ENUM(Config::TargetImplementation, RuntimeImplementation);
		GET_CFG_KEY_BOOL(Config::SecurityCritical);

		GET_CFG_KEY_STR(Config::ProfilerSettings);
		GET_CFG_KEY_BOOL(Config::MonoDebugger);
		GET_CFG_KEY_STR(Config::SystemLanguage);

		GET_CFG_KEY_STR(Config::PsmApps);

	}
	std::string Config::Mono21Folder() {
		return Path::Combine(std::string(Config::RunningFromDirectory), Path::Combine(Path::Combine(std::string(Config::RuntimeLibPath), "mono"), "2.1"));
	}

	std::string Config::PsmCoreLibPath() {
		return Path::Combine(Mono21Folder() , "Sce.PlayStation.Core.dll");
	}
	std::string Config::SystemLibPath() {
		return Path::Combine(Mono21Folder(), "System.dll");
	}
	std::string Config::MscorlibPath() {
		return Path::Combine(Mono21Folder(), "mscorlib.dll");
	}

	int Config::ScreenHeight(int idx) {
		return screenHeight;
	}

	int Config::ScreenWidth(int idx) {
		return screenWidth;
	}

	void Config::ReloadConfig() {
		Config::ReadConfig(Config::RunningFromDirectory, Config::cfgFilePath);
	}
	void Config::SaveConfig() {
		Config::WriteConfig(Config::cfgFilePath);
	}

	void Config::WriteConfig(const std::string& configFile) {
		Logger::Debug("Writing config file: " + configFile);
		std::ofstream cfgStream = std::ofstream(configFile);
		if (!cfgStream.fail()) {
			SET_CFG_COMMENT(cfgStream, "- Account information -");
			SET_CFG_KEY_STR(cfgStream, Config::Username);
			SET_CFG_KEY_UINT64(cfgStream, Config::AccountId);

			SET_CFG_COMMENT(cfgStream, "- Runtime Files -");
			SET_CFG_KEY_STR(cfgStream, Config::RuntimeLibPath);
			SET_CFG_KEY_STR(cfgStream, Config::RuntimeConfigPath);

			SET_CFG_COMMENT(cfgStream, "- Mono Settings -");
			SET_CFG_KEY_STR(cfgStream,  Config::ProfilerSettings);
			SET_CFG_KEY_BOOL(cfgStream, Config::SecurityCritical);
			SET_CFG_KEY_BOOL(cfgStream, Config::MonoDebugger);

			SET_CFG_COMMENT(cfgStream, "- SnowPME -");
			SET_CFG_KEY_STR(cfgStream, Config::PsmApps);
			SET_CFG_KEY_ENUM(cfgStream, Config::TargetImplementation);
			SET_CFG_KEY_STR(cfgStream, Config::SystemLanguage);

			cfgStream.close();
		}

	}
	void Config::ReadConfig(const std::string& runningFrom, const std::string& configFile) {
		Config::RunningFromDirectory = runningFrom;
		Config::cfgFilePath = Path::ChangeSlashesToNativeStyle(Path::Combine(Config::RunningFromDirectory, configFile));
		Logger::Debug("Reading config file: "+ Config::cfgFilePath);

		std::ifstream cfgStream = std::ifstream(Config::cfgFilePath);
		if (cfgStream.fail()) return WriteConfig(configFile);

		std::string ln;
		while (std::getline(cfgStream, ln)) {
			// check if line is a comment
			if (ln.starts_with(COMMENT)) continue;
			// get key value pair seperated by ":"
			std::vector<std::string> keyValues = StringUtil::Split(ln, SEPERATOR);
			if (keyValues.size() < 2) continue;

			// extract values into their own variables

			std::string key = keyValues.at(0);
			std::string value = keyValues.at(1);

			// parse the information
			parseKeyValuePair(key, value);
		}
	}
}