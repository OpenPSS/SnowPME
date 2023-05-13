#include <Sce/Pss/Core/Mono/Security.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
namespace Sce::Pss::Core::Mono
{
	std::string securityWhitelist[3]{
		"mscorlib.dll",
		"System.dll",
		"Sce.PlayStation.Core.dll"
	};

	int Security::IsSecurityCriticalExempt(const char* exeFullPath) {

		std::string exePath = std::string(exeFullPath);
		std::string filename = Shared::String::Path::GetFilename(exePath);
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