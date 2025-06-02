#include <Sce/Pss/Core/Io/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <string>

using namespace Shared::String;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Io::Edata {


	bool EdataList::IsFileInEdata(const std::string& path) {
		for (const std::string& edataFile : this->edataFilesList) {
			if (StringUtil::ToLower(edataFile) == StringUtil::ToLower(path)) {
				return true;
			}
		}
		return false;
	}

	EdataList::EdataList(std::string& psseListData) {		
		std::vector<std::string> psseFilesList = StringUtil::Split(StringUtil::Replace(psseListData, "\r", ""), "\n");

		for (const std::string& psseFile : psseFilesList) {
			if (psseFile.empty()) continue;

			Logger::Debug("EdataList // Registering file: " + psseFile);
			this->edataFilesList.push_back(psseFile);
		}
	}
}