#ifndef SHARED_PATH_H
#define SHARED_PATH_H 1

#include <string>

#define PSM_PATH_SEPERATOR "/"
#define WINDOWS_PATH_SEPERATOR "\\"
#define PSM_PATH_MAX (0xA0)

namespace Shared::String {

	class Path {
	public:
		static std::string ChangeSlashesToPsmStyle(const std::string& path);
		static std::string ChangeSlashesToNativeStyle(const std::string& path);
		static std::string MakeAbsolute(const std::string& workDir, const std::string& path);
		static std::string Combine(const std::string& path, const std::string& newPart);
		static std::string GetFilename(const std::string& path);
		static std::string UpDirectory(const std::string& path);
		static std::string NormalizePath(const std::string& workDir, const std::string& path);
	};
}

#endif