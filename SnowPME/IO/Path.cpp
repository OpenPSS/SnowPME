#include <IO/Path.hpp>
#include <IO/FileSystem.hpp>
#include <Util/StringUtils.hpp>
#include <vector>

using namespace SnowPME::Util;
namespace SnowPME::IO
{
	std::string Path::ChangeSlashesToPsmStyle(std::string path) {
		return StringUtils::Replace(path, WINDOWS_PATH_SEPERATOR, PSM_PATH_SEPERATOR); // Replace all \ with /.
	}

	std::string Path::Combine(std::string path, std::string newPart) {
		return path + PSM_PATH_SEPERATOR + newPart; // Append /newPart
	}

	std::string Path::GetFilename(std::string fullPath) {
		return ChangeSlashesToPsmStyle(fullPath).substr(ChangeSlashesToPsmStyle(fullPath).find_last_of(PSM_PATH_SEPERATOR) + 1);
	}

}