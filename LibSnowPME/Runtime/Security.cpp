#include <Runtime/Security.hpp>
#include <Util/Config.hpp>
#include <Debug/Logger.hpp>
#include <LibPSM.hpp>

using namespace Sce::Pss::Core::Io;
using namespace SnowPME::Debug;
namespace SnowPME::Runtime
{
	std::string securityWhitelist[3]{
		"mscorlib.dll",
		"System.dll",
		"Sce.PlayStation.Core.dll"
	};

	int Security::IsSecurityCriticalExempt(const char* exeFullPath) {

		std::string exePath = std::string(exeFullPath);
		std::string filename = Path::GetFilename(exePath);
		for (std::string exemptFilename : securityWhitelist) {
			if (filename == exemptFilename) {
				Logger::Debug("Determined Security Level for : " + filename + " as [SecurityCritical]");
				return true;
			}
		}
		Logger::Debug("Determined Security Level for : " + filename + " as [SecurityTransparent]");
		return false;
	}


}