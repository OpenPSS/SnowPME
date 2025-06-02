#ifndef LIB_PSS_EDATALIST_H
#define LIB_PSS_EDATALIST_H 1
#include <vector>
#include <string>

namespace Sce::Pss::Core::Io::Edata {
	class EdataList {
	private:
		std::vector<std::string> edataFilesList;
	public:
		bool IsFileInEdata(const std::string& path);
		EdataList(std::string& psseListData);
	};
}

#endif