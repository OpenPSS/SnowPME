#ifndef SHARED_CONFIG_H
#define SHARED_CONFIG_H 1
#include <RuntimeImplementation.hpp>
#include <string>
namespace Shared
{
#define GET_CFG_KEY_STR(name) if (key == #name) Config::name = value
#define GET_CFG_KEY_UINT64(name) if (key == #name) Config::name = strtoull(value.c_str(), NULL, 16)
#define GET_CFG_KEY_ENUM(name, enumName) if (key == #name) Config::name = (enumName)strtoull(value.c_str(), NULL, 16)
#define GET_CFG_KEY_BOOL(name) if (key == #name) Config::name = (value == "true")

#define SET_CFG_COMMENT(str, cmt) str << COMMENT << cmt << std::endl;
#define SET_CFG_KEY_STR(str, name) str << #name << SEPERATOR << Config::name << std::endl;
#define SET_CFG_KEY_UINT64(str, name) str << #name << SEPERATOR <<  std::hex << (uint64_t)Config::name << std::endl;
#define SET_CFG_KEY_ENUM(str, name) SET_CFG_KEY_UINT64(str, name)
#define SET_CFG_KEY_BOOL(str, name) str << #name << SEPERATOR <<  (Config::name ? "true" : "false") << std::endl;

	class Config {
	private:
		static void parseKeyValuePair(std::string key, std::string value); // parses the line read from the cfg file
		static std::string mono21Folder(); // gets RuntimeLibPath /mono/2.1
	public:
		static bool SecurityCritical; // If mono is allowed full access to native functions.
		static std::string RuntimeLibPath; // Path to the folder containing all DLLs
		static std::string RuntimeConfigPath; // Path to the folder containing the machine.config file.
		
		static int ScreenTotal; // How many screens? 
		static std::string Username; // Username
		static uint64_t AccountId; // Account Name
		static RuntimeImplementation TargetImplementation; // What version of psm runtime are we emulating?

		static int ScreenWidth(int idx);
		static int ScreenHeight(int idx);

		static std::string PsmCoreLibPath(); // Path to Sce.PlayStation.Core.dll
		static std::string SystemLibPath();  // Path to System.dll
		static std::string MscorlibPath();  // Path to mscorlib.dll

		static void WriteConfig(std::string configFile);
		static void ReadConfig(std::string configFile);
	};
}
#endif