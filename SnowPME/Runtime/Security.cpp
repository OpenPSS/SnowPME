#include <Runtime/Security.hpp>
#include <Util/Config.hpp>
#include <Debug/Logger.hpp>

using namespace SnowPME::Debug;
namespace SnowPME::Runtime
{
	std::string securityWhitelist[3]{
		"mscorlib.dll",
		"System.dll",
		"Sce.PlayStation.Core.dll"
	};

	int Security::IsSecurityCriticalExempt(const char* exeFullPath) {

		std::string path(exeFullPath);
		std::string filename = path.substr(path.find_last_of("/\\") + 1);
		for (std::string exemptFilename : securityWhitelist) {
			if (filename == exemptFilename) {
				Logger::Debug("Determined Security Level for : " + filename + " as [SecurityCritical]");
				return true;
			}
		}
		Logger::Debug("Determined Security Level for : " + filename + " as [SecuritySafeCritical]");
		return false;
	}


}