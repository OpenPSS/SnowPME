#include <Config.hpp>
#include <String/Path.hpp>
#include <String/StringUtil.hpp>
#include <Debug/Logger.hpp>
#include <fstream>
#include <string>

using namespace Shared::String;
using namespace Shared::Debug;

namespace Shared
{
	static const std::string SEPERATOR = ":";
	static const std::string COMMENT = "#";
	static const std::string DEFAULT_RUNTIME_FOLDER = "RUNTIME";
	static const std::string DEFAULT_CONFIG_FOLDER = "CONFIG";

	static int screenWidth = 960;
	static int screenHeight = 544;
	int Config::ScreenTotal = 1;
	bool Config::SecurityCritical = false;


	std::string Config::RuntimeLibPath = DEFAULT_RUNTIME_FOLDER;
	std::string Config::RuntimeConfigPath = DEFAULT_RUNTIME_FOLDER;

	std::string Config::Username = "Li";
	uint64_t Config::AccountId = 0x0000000000000000;
	RuntimeImplementation Config::TargetImplementation = RuntimeImplementation::PSVita;


	void Config::parseKeyValuePair(std::string key, std::string value) {
		GET_CFG_KEY_STR(Username);
		GET_CFG_KEY_UINT64(AccountId);

		GET_CFG_KEY_STR(RuntimeLibPath);
		GET_CFG_KEY_STR(RuntimeConfigPath);

		GET_CFG_KEY_ENUM(TargetImplementation, RuntimeImplementation);
		GET_CFG_KEY_BOOL(SecurityCritical);

	}
	std::string Config::mono21Folder() {
		return Path::Combine(Path::Combine(Config::RuntimeLibPath, "mono"), "2.1");
	}

	std::string Config::PsmCoreLibPath() {
		return Path::Combine(mono21Folder() , "Sce.PlayStation.Core.dll");
	}
	std::string Config::SystemLibPath() {
		return Path::Combine(mono21Folder(), "System.dll");
	}
	std::string Config::MscorlibPath() {
		return Path::Combine(mono21Folder(), "mscorlib.dll");
	}

	int Config::ScreenHeight(int idx) {
		return screenHeight;
	}

	int Config::ScreenWidth(int idx) {
		return screenWidth;
	}
	void Config::WriteConfig(std::string configFile) {
		std::ofstream cfgStream = std::ofstream(configFile);
		if (!cfgStream.fail()) {
			SET_CFG_COMMENT(cfgStream, "- Account information -");
			SET_CFG_KEY_STR(cfgStream, Username);
			SET_CFG_KEY_UINT64(cfgStream, AccountId);

			SET_CFG_COMMENT(cfgStream, "- Runtime Files -");
			SET_CFG_KEY_STR(cfgStream, RuntimeLibPath);
			SET_CFG_KEY_STR(cfgStream, RuntimeConfigPath);

			SET_CFG_COMMENT(cfgStream, "- Implementation Details -");
			SET_CFG_KEY_ENUM(cfgStream, TargetImplementation);
			SET_CFG_KEY_BOOL(cfgStream, SecurityCritical);

			cfgStream.close();
		}

	}
	void Config::ReadConfig(std::string configFile) {
		std::ifstream cfgStream = std::ifstream(configFile);
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