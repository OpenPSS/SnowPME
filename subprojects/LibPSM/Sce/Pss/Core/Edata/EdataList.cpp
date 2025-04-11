#include <Sce/Pss/Core/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <string>

namespace Sce::Pss::Core::Edata {
	using namespace Shared::String;
	using namespace Shared::Debug;

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
			Logger::Debug("Registering file: " + psseFile);
			this->edataFilesList.push_back(psseFile);
		}
	}
}