#ifndef SNOW_PME_PATH_H
#define SNOW_PME_PATH_H 1

#include <string>
#include <filesystem>
#include <iostream>

#define PSM_PATH_SEPERATOR "/"
#define WINDOWS_PATH_SEPERATOR "\\"

namespace SnowPME::Io
{
	class Path {
	public:
		static std::string GetAbsolutePath(std::string path);
		static std::string ChangeSlashesToPsmStyle(std::string path);
		static bool IsSandboxDirectory(std::string path);
	};
}

#endif