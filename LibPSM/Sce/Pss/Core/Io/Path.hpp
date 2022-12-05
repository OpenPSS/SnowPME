#ifndef LIB_PSM_PATH_H
#define LIB_PSM_PATH_H 1

#include <string>

#define PSM_PATH_SEPERATOR "/"
#define WINDOWS_PATH_SEPERATOR "\\"
#define PSM_PATH_MAX (0xA0)

namespace Sce::Pss::Core::Io {

	class Path {
	public:
		static std::string ChangeSlashesToPsmStyle(std::string path);
		static std::string ChangeSlashesToNativeStyle(std::string path);
		static std::string Combine(std::string path, std::string newPart);
		static std::string GetFilename(std::string path);
		static std::string UpDirectory(std::string path);
	};
}

#endif