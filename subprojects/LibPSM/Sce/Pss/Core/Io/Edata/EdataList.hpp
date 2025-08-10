#ifndef LIB_PSS_EDATALIST_H
#define LIB_PSS_EDATALIST_H 1
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <vector>
#include <string>

namespace Sce::Pss::Core::Io::Edata {
	const std::string EdataListPath = "/Application/edata.list";
	const std::string PsseListPath = "/Application/psse.list";

	class EdataList {
	private:
		static std::vector<std::string> edataFilesList;
		static void parseEdataList(const std::string& psseListData, Sandbox* sandbox);
	public:
		static bool IsFileInEdata(const std::string& path);
		static int ReadPsseOrEdataList(uint8_t klicensee[0x10] = nullptr, Sandbox* sandbox = nullptr);
	};
}

#endif