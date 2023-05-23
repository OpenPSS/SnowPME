#ifndef LIB_PSM_PLATFORM_SPECIFIC_H
#define LIB_PSM_PLATFORM_SPECIFIC_H 1
#include <cstdint>
#include <string>

namespace Sce::Pss::Core {

	#define FILETIME_TICK 10000000LL
	#define UNIX_EPOCH 11644473600LL

	#define FILETIME_TO_UNIX(filetime) (time_t)(filetime == -1 ? filetime : filetime / FILETIME_TICK - UNIX_EPOCH);
	#define UNIX_TO_FILETIME(unixtime) ((unixtime+UNIX_EPOCH) * FILETIME_TICK);

	#ifdef _MSC_VER
		typedef wchar_t wchar;
	#endif

	class PlatformSpecific {
	public:
		static int ChangeFileAttributes(std::string RealFilePath, uint32_t attribute);
		static int ChangeFileTimes(std::string RealFilePath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime);
		static std::string Username();
	};
}

#endif