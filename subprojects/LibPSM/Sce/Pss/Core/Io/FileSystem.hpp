#ifndef LIB_PSS_FILESYSTEM_H
#define LIB_PSS_FILESYSTEM_H 1

#include <string>
#include <filesystem>
#include <memory>
#include <Sce/Pss/Core/Io/Edata/PsmDrm.hpp>

namespace Sce::Pss::Core::Io {
	class FileSystem {
	private:
		bool rewritable = false;
		bool root = false;
		bool system = false;
		std::string pathOnDisk = "";
		std::string pathInSandbox = "";
		
	public:
		FileSystem(const std::string& filesystemPath, const std::string& sandboxPathName, bool rewritable, bool root, bool system);
		~FileSystem() = default;

		std::string SandboxPath();
		std::string PathOnDisk();
		bool IsWritable();
		bool IsRoot();
		bool IsSystem();
	};
}

#endif