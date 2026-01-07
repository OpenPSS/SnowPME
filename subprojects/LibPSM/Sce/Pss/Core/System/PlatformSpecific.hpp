#ifndef LIB_PSS_PLATFORM_SPECIFIC_H
#define LIB_PSS_PLATFORM_SPECIFIC_H 1
#include <cstdint>
#include <string>
#include <LibShared.hpp>

namespace Sce::Pss::Core::System {

	#define FILETIME_TICK 10000000LL
	#define UNIX_EPOCH 11644473600LL

	#define FILETIME_TO_UNIX(filetime) (time_t)(filetime == -1 ? filetime : filetime / FILETIME_TICK - UNIX_EPOCH);
	#define UNIX_TO_FILETIME(unixtime) ((unixtime+UNIX_EPOCH) * FILETIME_TICK);


	class PlatformSpecific {
	private:
		static std::string escapeShellArgument(std::string arg);
	public:
		static int ChangeFileAttributes(std::string RealFilePath, uint32_t attribute);
		static int ChangeFileTimes(std::string RealFilePath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime);
		static int OpenWebsite(std::string url);
	};
}

#endif