#ifndef SNOW_PME_PATH_H
#define SNOW_PME_PATH_H 1

#include <string>

namespace SnowPME::IO
{
	class Path {
	public:
		static std::string ChangeSlashesToPsmStyle(std::string path);
		static std::string Combine(std::string path, std::string newPart);
	};
}

#endif