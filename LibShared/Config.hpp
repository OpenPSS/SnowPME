#ifndef SHARED_CONFIG_H
#define SHARED_CONFIG_H 1
#include <string>

namespace Shared
{
	class Config {
	private:
	public:
		static bool SecurityCritical; // If mono is allowed full access to native functions.
		static std::string PsmCoreLibPath; // Path to Sce.PlayStation.Core.dll
		static std::string SystemLibPath; // Path to System.dll
		static std::string MscorlibPath; // Path to mscorlib.dll

		static std::string RuntimeSystemPath; // Path to System.dll
		static std::string RuntimeLibPath; // Path to lib folder.
		static std::string RuntimeMonoPath; // Path to lib/mono folder.
		static std::string RuntimeVerisonPath; // Path to lib/2.1 folder.
		static std::string PsmLibsPath; // Path to lib/psm folder


		static std::string RuntimeConfigPath; // Path to etc folder.
		
		static int ScreenWidth(int idx);
		static int ScreenHeight(int idx);
		static int ScreenTotal();

		static int ReadConfig(std::string configFile);
	};
}
#endif