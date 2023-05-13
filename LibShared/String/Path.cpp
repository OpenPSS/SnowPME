#include <String/Util.hpp>
#include <String/Path.hpp>
#include <vector>

namespace Shared::String {
	std::string Path::ChangeSlashesToPsmStyle(std::string path) {
		return Shared::String::Util::Replace(path, WINDOWS_PATH_SEPERATOR, PSM_PATH_SEPERATOR); // Replace all \ with /.
	}

	std::string Path::ChangeSlashesToNativeStyle(std::string path) {
#ifdef _WIN32
		return Shared::String::Util::Replace(path, PSM_PATH_SEPERATOR, WINDOWS_PATH_SEPERATOR); // Replace all / with \.
#else
		return ChangeSlashesToPsmStyle(path); // *NIX and PSM use the same style.
#endif
	}

	std::string Path::Combine(std::string path, std::string newPart) {
		if (path == "")
			return newPart;

		return path + PSM_PATH_SEPERATOR + newPart; // Append /newPart
	}

	std::string Path::GetFilename(std::string fullPath) {
		return ChangeSlashesToPsmStyle(fullPath).substr(ChangeSlashesToPsmStyle(fullPath).find_last_of(PSM_PATH_SEPERATOR) + 1);
	}

	std::string Path::UpDirectory(std::string fullPath) {
		std::string filename = GetFilename(fullPath);
		return fullPath.substr(0, fullPath.length() - (filename.length()+1));
	}

}