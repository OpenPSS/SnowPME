#ifndef LIB_PSS_FILESYSTEM_H
#define LIB_PSS_FILESYSTEM_H 1

#include <string>
#include <filesystem>
#include <Sce/Pss/Core/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Edata/EdataList.hpp>

namespace Sce::Pss::Core::Io {
	class FileSystem {
	private:
		bool rw = false;
		bool emulated = false;
		bool system = false;
		std::string pathOnDisk = "";
		std::string sandboxPath = "";
		
		Sce::Pss::Core::Edata::EdataList* edataList = nullptr;
		int readEdataList(Sce::Pss::Core::Edata::PsmDrm* psmDrm = nullptr);

	public:
		FileSystem(std::string filesystemPath, std::string sandboxPathName, bool rewritable, bool emulated, bool system);
		~FileSystem();

		std::string SandboxPath();
		std::string PathOnDisk();
		Sce::Pss::Core::Edata::EdataList* GetEdataList(Sce::Pss::Core::Edata::PsmDrm* psmDrm = nullptr);
		bool IsRewitable();
		bool IsEmulated();
		bool IsSystem();
	};
}

#endif