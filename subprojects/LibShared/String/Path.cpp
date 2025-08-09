#include <String/Format.hpp>
#include <String/Path.hpp>
#include <filesystem>

#include <vector>

namespace Shared::String {
	std::string Path::ChangeSlashesToPsmStyle(const std::string& path) {
		return Format::Replace(path, WINDOWS_PATH_SEPERATOR, PSM_PATH_SEPERATOR); // Replace all \ with /.
	}

	std::string Path::ChangeSlashesToNativeStyle(const std::string& path) {
#ifdef _WIN32
		return Format::Replace(path, PSM_PATH_SEPERATOR, WINDOWS_PATH_SEPERATOR); // Replace all / with \.
#else
		return ChangeSlashesToPsmStyle(path); // *NIX and PSM use the same style.
#endif
	}

	std::string Path::MakeAbsolute(const std::string& workDir, const std::string& path) {
		std::string nativePath = Path::ChangeSlashesToNativeStyle(path);
		std::string nativeWorkDir = Path::ChangeSlashesToNativeStyle(workDir);
		if (!std::filesystem::path(nativePath).is_absolute()) {
			return Path::ChangeSlashesToNativeStyle(Path::Combine(nativeWorkDir, nativePath));
		}
		return nativePath;
	}

	std::string Path::Combine(const std::string& path, const std::string& newPart) {
		if (path == "")
			return ChangeSlashesToPsmStyle(newPart);

		return ChangeSlashesToPsmStyle(path + PSM_PATH_SEPERATOR + newPart); // Append /newPart
	}

	std::string Path::GetFilename(const std::string& fullPath) {
		return ChangeSlashesToPsmStyle(fullPath).substr(ChangeSlashesToPsmStyle(fullPath).find_last_of(PSM_PATH_SEPERATOR) + 1);
	}

	std::string Path::UpDirectory(const std::string& fullPath) {
		std::string filename = GetFilename(fullPath);
		return fullPath.substr(0, fullPath.length() - (filename.length()+1));
	}

	std::string Path::NormalizePath(const std::string& workDir, const std::string& path) {
		// Split path by the / seperator
		std::vector<std::string> normalizedPathComponents;
		std::vector<std::string> pathComponents = Format::Split(Path::ChangeSlashesToPsmStyle(path), PSM_PATH_SEPERATOR);

		// if you think about it, file paths are essentially. just First-In-First-Out (FIFO);
		for (std::string pathComponent : pathComponents) {
			if (pathComponent == ".") { // . indicates the current directory, so just nop
				continue;
			}
			else if (pathComponent == "..") { // .. indicates to go back one directory, basically, pop
				if (normalizedPathComponents.size() >= 1)
					normalizedPathComponents.pop_back();
				continue;
			}
			else { // everything else is actually part of the path, basically push
				normalizedPathComponents.push_back(pathComponent);
			}
		}

		std::string normalizedPath = Path::Combine(workDir, Format::Join(normalizedPathComponents, PSM_PATH_SEPERATOR));
		return normalizedPath;
	}

}