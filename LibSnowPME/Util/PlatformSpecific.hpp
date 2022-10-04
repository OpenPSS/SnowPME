#ifndef SNOW_PME_PLATFORM_SPECIFIC_H
#define SNOW_PME_PLATFORM_SPECIFIC_H 1
#include <cstdint>
#include <string>



namespace SnowPME::Util {
	class PlatformSpecific {
	public:
		static int ChangeFileAttributes(std::string RealFilePath, uint32_t attribute);
		static int ChangeFileTimes(std::string RealFilePath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime);
		static uint64_t CurrentThreadId();
	};
}

#endif