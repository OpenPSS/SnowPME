#include <Runtime/Security.hpp>
#include <Util/Config.hpp>

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
#ifdef _DEBUG
		std::cout << "Determining Security Level for : " << filename;
#endif
		for (std::string exemptFilename : securityWhitelist) {
			if (filename == exemptFilename) {
#ifdef _DEBUG
				std::cout << " [SecurityCritical]" << std::endl;
#endif
				return true;
			}
		}
#ifdef _DEBUG
		std::cout << " [SecuritySafeCritical]" << std::endl;
#endif
		return false;
	}


}