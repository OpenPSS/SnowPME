#ifndef SNOW_PME_FILESYSTEM_H
#define SNOW_PME_FILESYSTEM_H 1

#include <string>

#define PSM_PATH_SEPERATOR "/"
#define WINDOWS_PATH_SEPERATOR "\\"
#define PSM_PATH_MAX (0xAC)

namespace SnowPME::IO{
	class FileSystem {
	private:
		static std::string currentWorkingDirectory;

		bool rewritable;
		std::byte gamekey[0x20];
		std::string filesystemPath;
	public:
		FileSystem(std::string path, std::string sandboxPathName, bool rewritable, bool encrypted);
		~FileSystem();

		std::string AbsolutePath(std::string path);
		bool IsDirectory(std::string path);
		bool IsRewitable();
	};
}

#endif