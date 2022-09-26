#ifndef SNOW_PME_PLATFORM_SPECIFIC_H
#define SNOW_PME_PLATFORM_SPECIFIC_H 1
#include <cstdint>
#include <string>



namespace SnowPME::IO {
	class PlatformSpecific {
	public:
		static int ChangeFileTimes(std::string RealFilePath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime);
	};
}

#endif