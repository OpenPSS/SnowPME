#ifndef SHARED_CONFIG_H
#define SHARED_CONFIG_H 1
#include <RuntimeImplementation.hpp>
#include <string>
#include <cstdint>

namespace Shared {
	class Config {
	private:
		static void parseKeyValuePair(std::string key, std::string value); // parses the line read from the cfg file
		static std::string cfgFilePath; // path to the config file that is being read;

	public:
		static char RuntimeLibPath[0x1028]; // Path to the folder containing all DLLs
		static char RuntimeConfigPath[0x1028]; // Path to the folder containing the machine.config file.
		static char PsmApps[0x1028]; // Install location of playstation mobile games

		static std::string RunningFromDirectory; // Path to the folder containing the main executable.
		static bool DebugLogging; // if should provide extended logging (DEBUG channel)
		static bool SecurityCritical; // If mono is allowed full access to native functions.
		static char SystemLanguage[0x1028]; // System language to emulate

		static char ProfilerSettings[0x1028];
		static bool MonoDebugger;
		
		static int ScreenTotal; // How many screens? 
		static char Username[0x1028]; // Username
		static uint64_t AccountId; // Account Name
		static RuntimeImplementation TargetImplementation; // What version of psm runtime are we emulating?
		
		static int ScreenWidth(int idx);
		static int ScreenHeight(int idx);

		static std::string GetPsmAppsFolder(); // gets PSM/ folder Path
		static std::string GetRuntimeLibraryFolder(); // gets Runtime Libraries Path
		static std::string GetRuntimeConfigFolder(); // gets Runtime Configuration Path
		static std::string GetScePlaystationCoreDllPath(); // Path to Sce.PlayStation.Core.dll
		static std::string GetSystemDllPath();  // Path to System.dll
		static std::string GetCorlibDllPath();  // Path to mscorlib.dll

		static void SaveConfig();
		static void ReloadConfig();

		static void WriteConfig(const std::string& configFile);
		static void ReadConfig(const std::string& runningFrom, const std::string& configFile);

		static bool ValidateConifg();
	};
}
#endif