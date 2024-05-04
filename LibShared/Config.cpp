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

	std::string Config::RunningFromDirectory = "";
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
	std::string Config::Mono21Folder() {
		return Path::Combine(Config::RunningFromDirectory, Path::Combine(Path::Combine(Config::RuntimeLibPath, "mono"), "2.1"));
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
	void Config::ReadConfig(std::string runningFrom, std::string configFile) {
		Config::RunningFromDirectory = runningFrom;
		std::string cfgFilePath = Path::ChangeSlashesToNativeStyle(Path::Combine(Config::RunningFromDirectory, configFile));
		Logger::Debug("Reading config file: "+cfgFilePath);

		std::ifstream cfgStream = std::ifstream(cfgFilePath);
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