#ifndef LIB_PSS_FILESYSTEM_H
#define LIB_PSS_FILESYSTEM_H 1

#include <string>
#include <filesystem>
#include <Sce/Pss/Core/Io/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataList.hpp>

namespace Sce::Pss::Core::Io {
	class FileSystem {
	private:
		bool rewritable = false;
		bool root = false;
		bool system = false;
		std::string pathOnDisk = "";
		std::string pathInSandbox = "";
		
		Sce::Pss::Core::Io::Edata::EdataList* edataList = nullptr;
		int readEdataList(Sce::Pss::Core::Io::Edata::PsmDrm* psmDrm = nullptr);

	public:
		FileSystem(const std::string& filesystemPath, const std::string& sandboxPathName, bool rewritable, bool root, bool system);
		~FileSystem();

		std::string SandboxPath();
		std::string PathOnDisk();
		Sce::Pss::Core::Io::Edata::EdataList* GetEdataList(Sce::Pss::Core::Io::Edata::PsmDrm* psmDrm = nullptr);
		bool IsWritable();
		bool IsRoot();
		bool IsSystem();
	};
}

#endif