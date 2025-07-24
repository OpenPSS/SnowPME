#include <Config.hpp>
#include <String/Path.hpp>
#include <String/Format.hpp>
#include <Debug/Logger.hpp>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstring>

using namespace Shared::String;
using namespace Shared::Debug;

#define GET_CFG_KEY_STR(name) if (key == #name) strncpy(name, value.c_str(), sizeof(name)-1)
#define GET_CFG_KEY_UINT64(name) if (key == #name) name = strtoull(value.c_str(), nullptr, 16)
#define GET_CFG_KEY_ENUM(name, enumName) if (key == #name) name = (enumName)strtoull(value.c_str(), nullptr, 16)
#define GET_CFG_KEY_BOOL(name) if (key == #name) name = (value == "true")

#define SET_CFG_COMMENT(str, cmt) str << COMMENT << cmt << std::endl;
#define SET_CFG_KEY_STR(str, name) str << #name << SEPERATOR << std::string(name) << std::endl;
#define SET_CFG_KEY_UINT64(str, name) str << #name << SEPERATOR <<  std::hex << static_cast<uint64_t>(name) << std::endl;
#define SET_CFG_KEY_ENUM(str, name) SET_CFG_KEY_UINT64(str, name)
#define SET_CFG_KEY_BOOL(str, name) str << #name << SEPERATOR <<  (name ? "true" : "false") << std::endl;

#define VALIDATE_FILESYSTEM(path, prettyDesc) if (!std::filesystem::exists(path)) { Logger::Error("Cannot find " prettyDesc " [" + std::string(path) + "]"); isValid = false; }

namespace Shared
{

	static const std::string SEPERATOR = "=";
	static const std::string COMMENT = "#";

	static int screenWidth = 960;
	static int screenHeight = 544;
	std::string Config::cfgFilePath = "";

	std::string Config::RunningFromDirectory = "";

	int Config::ScreenTotal = 1;
	bool Config::SecurityCritical = false;
#ifdef _DEBUG
	bool Config::DebugLogging = true;
#else
	bool Config::DebugLogging = false;
#endif
	char Config::RuntimeLibPath[0x1028] = "dll";
	char Config::RuntimeConfigPath[0x1028] = "dll";

	char Config::Username[0x1028] = "SnowPME";
	char Config::SystemLanguage[0x1028] = "en-US";

	uint64_t Config::AccountId = 0x123456789ABCDEF0ull;
	RuntimeImplementation Config::TargetImplementation = RuntimeImplementation::PSVita;

	bool Config::MonoDebugger = false;
	char Config::ProfilerSettings[0x1028] = "";
	char Config::PsmApps[0x1028] = "psm";

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
		GET_CFG_KEY_BOOL(Config::DebugLogging);

		GET_CFG_KEY_STR(Config::PsmApps);

	}

	std::string Config::GetPsmAppsFolder() {
		if (std::filesystem::path(Config::PsmApps).is_relative()) return Path::Combine(Config::RunningFromDirectory, Config::PsmApps);
		else return Config::PsmApps;
	}

	std::string Config::GetRuntimeLibraryFolder() {
		std::string expectedPath = std::filesystem::path(Config::RuntimeLibPath).is_relative() ? Path::Combine(Config::RunningFromDirectory, Config::RuntimeLibPath) : Config::RuntimeLibPath;

		// if not found; lookup the file from inside the PSM SDK; (if installed)
		if (!std::filesystem::exists(expectedPath)) {
			char* psmSdk = getenv("SCE_PSM_SDK");
			if (psmSdk != nullptr) {
				std::string gotPath = Path::Combine(Path::Combine(Path::Combine(Path::Combine(psmSdk, "mono"), "lib"), "mono"), "2.1");
				if (std::filesystem::exists(gotPath)) return gotPath;
			}
		}


		return expectedPath;
	}

	std::string Config::GetRuntimeConfigFolder() {
		std::string expectedPath = std::filesystem::path(Config::RuntimeConfigPath).is_relative() ? Path::Combine(Config::RunningFromDirectory, Config::RuntimeConfigPath) : Config::RuntimeConfigPath;

		// if not found; lookup the file from inside the PSM SDK; (if installed)
		if (!std::filesystem::exists(expectedPath)) {
			char* psmSdk = getenv("SCE_PSM_SDK");
			if (psmSdk != nullptr) {
				std::string gotPath = Path::Combine(Path::Combine(psmSdk, "mono"), "etc");
				if (std::filesystem::exists(gotPath)) return gotPath;
			}
		}

		return expectedPath;
	}

	std::string Config::GetMono21Folder() {
		std::string expectedPath = GetRuntimeLibraryFolder();

		// if not found; lookup the file from inside the PSM SDK; (if installed)
		if (!std::filesystem::exists(expectedPath)) {
			char* psmSdk = getenv("SCE_PSM_SDK");
			if (psmSdk != nullptr) {
				std::string gotPath = Path::Combine(Path::Combine(Path::Combine(Path::Combine(psmSdk, "mono"), "lib"), "mono"), "2.1");
				if (std::filesystem::exists(gotPath)) return gotPath;
			}
		}


		return expectedPath;
	}

	std::string Config::GetPsmCoreLibPath() {
		std::string expectedPath = Path::Combine(GetMono21Folder() , "Sce.PlayStation.Core.dll");
		
		// if not found; lookup the file from inside the PSM SDK; (if installed)
		if (!std::filesystem::exists(expectedPath)) {
			char* psmSdk = getenv("SCE_PSM_SDK");
			if (psmSdk != nullptr) {
				std::string gotPath = Path::Combine(Path::Combine(Path::Combine(Path::Combine(psmSdk, "mono"), "lib"), "psm"), "Sce.PlayStation.Core.dll");
				if (std::filesystem::exists(gotPath)) return gotPath;
			}
		}

		return expectedPath;
	}
	std::string Config::GetSystemLibPath() {
		std::string expectedPath = Path::Combine(GetMono21Folder(), "System.dll");

		// if not found; lookup the file from inside the PSM SDK; (if installed)
		if (!std::filesystem::exists(expectedPath)) {
			char* psmSdk = getenv("SCE_PSM_SDK");
			if (psmSdk != nullptr) {
				std::string gotPath = Path::Combine(Path::Combine(Path::Combine(Path::Combine(Path::Combine(psmSdk, "mono"), "lib"), "mono"), "2.1"), "System.dll");
				if (std::filesystem::exists(gotPath)) return gotPath;
			}
		}

		return expectedPath;
	}
	std::string Config::GetMscorlibPath() {
		std::string expectedPath = Path::Combine(GetMono21Folder(), "mscorlib.dll");

		// if not found; lookup the file from inside the PSM SDK; (if installed)
		if (!std::filesystem::exists(expectedPath)) {
			char* psmSdk = getenv("SCE_PSM_SDK");
			if (psmSdk != nullptr) {
				std::string gotPath = Path::Combine(Path::Combine(Path::Combine(Path::Combine(Path::Combine(psmSdk, "mono"), "lib"), "mono"), "2.1"), "mscorlib.dll");
				if (std::filesystem::exists(gotPath)) return gotPath;
			}
		}

		return expectedPath;
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
		Logger::Debug("Writing config file: [" + Config::cfgFilePath + "]");
		std::ofstream cfgStream = std::ofstream(Config::cfgFilePath);
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
			SET_CFG_KEY_BOOL(cfgStream, Config::DebugLogging);


			cfgStream.close();
		}

	}

	bool Config::ValidateConifg() {

		bool isValid = true;

		VALIDATE_FILESYSTEM(Config::GetMscorlibPath(), "mscorlib.dll");
		VALIDATE_FILESYSTEM(Config::GetSystemLibPath(), "System.dll");
		VALIDATE_FILESYSTEM(Config::GetPsmCoreLibPath(), "Sce.PlayStation.Core.dll");

		return isValid;
	}
	
	void Config::ReadConfig(const std::string& runningFrom, const std::string& configFile) {
		Config::RunningFromDirectory = runningFrom;
		Config::cfgFilePath = std::filesystem::path(configFile).is_relative() ? Path::ChangeSlashesToNativeStyle(Path::Combine(Config::RunningFromDirectory, configFile)) : configFile;
		Logger::Debug("Reading config file: ["+ Config::cfgFilePath+"]");

		std::ifstream cfgStream = std::ifstream(Config::cfgFilePath);
		if (cfgStream.fail()) return WriteConfig(configFile);

		std::string ln;
		while (std::getline(cfgStream, ln)) {
			// check if line is a comment
			if (ln.starts_with(COMMENT)) continue;
			// get key value pair seperated by ":"
			std::vector<std::string> keyValues = Format::Split(ln, SEPERATOR);
			if (keyValues.size() < 2) continue;

			// extract values into their own variables

			std::string key = keyValues.at(0);
			std::string value = keyValues.at(1);

			// parse the information
			parseKeyValuePair(key, value);
		}
	}
}