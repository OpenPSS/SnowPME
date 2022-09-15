#include <IO/FileSystem.hpp>
#include <IO/Path.hpp>
#include <Util/StringUtils.hpp>

#include <vector>
using namespace SnowPME::Util;

namespace SnowPME::IO {
	bool FileSystem::IsDirectory(std::string path) {
		// Convert to absolute path
		std::string pathToCheck = AbsolutePath(path);


		// Valid sandbox folders
		/*std::string sandboxFolders[5] = {
			"/Documents",
			"/Temp",
			"/Application",
			"/fonts",
			"/"
		};

		// Iterate over all possible sandbox folders
		for (std::string sandboxFolder : sandboxFolders) {
			if (StringUtils::ToLower(path) == StringUtils::ToLower(sandboxFolder)) // If path starts with sandbox folder name
			{
				return true;
			}
		}*/

		return false;
	}


	std::string FileSystem::AbsolutePath(std::string relativePath) {
		std::vector<std::string> absolutePathComponents;

		// Split path by the / seperator
		std::vector<std::string> pathComponents = StringUtils::Split(Path::ChangeSlashesToPsmStyle(relativePath), PSM_PATH_SEPERATOR);

		// if you think about it, file paths are essentially. just First-In-First-Out much like The Stack,

		for (std::string pathComponent : pathComponents) {
			if (pathComponent == ".") { // . indicates the current directory, so just nop
				continue;
			}
			else if (pathComponent == "..") { // .. indicates to go back one directory, basically, pop
				if (absolutePathComponents.size() >= 1)
					absolutePathComponents.pop_back();
				continue;
			}
			else { // everything else is actually part of the path, basically push
				absolutePathComponents.push_back(pathComponent);
			}
		}

		std::string absolutePath = "/" + StringUtils::Join(absolutePathComponents, PSM_PATH_SEPERATOR);
		absolutePath = absolutePath.substr(0, PSM_PATH_MAX);
		return absolutePath;
	}
}
