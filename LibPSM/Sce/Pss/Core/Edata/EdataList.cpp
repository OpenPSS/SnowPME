#include <Sce/Pss/Core/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <string>

using namespace Shared::String;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Edata {
	bool EdataList::IsFileInEdata(std::string path) {
		for (std::string edataFile : this->edataFilesList) {
			if (StringUtil::ToLower(edataFile) == StringUtil::ToLower(path)) {
				return true;
			}
		}
		return false;
	}

	EdataList::EdataList(std::string psseListData) {		
		psseListData = StringUtil::Replace(psseListData, "\r", "");
		std::vector<std::string> psseFilesList = StringUtil::Split(psseListData, "\n");

		for (std::string psseFile : psseFilesList) {
			Logger::Debug("Registering file: " + psseFile);
			this->edataFilesList.push_back(psseFile);
		}
	}
}