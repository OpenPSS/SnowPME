#ifndef LIB_PSS_FILESYSTEM_H
#define LIB_PSS_FILESYSTEM_H 1

#include <string>
#include <filesystem>

namespace Sce::Pss::Core::Io {
	class FileSystem {
	private:
		bool rw = false;
		bool emulated = false;
		bool system = false;
		std::string pathOnDisk = "";
		std::string sandboxPath = "";
	public:
		FileSystem(std::string filesystemPath, std::string sandboxPathName, bool rewritable, bool emulated, bool system);
		~FileSystem();

		std::string SandboxPath();
		std::string PathOnDisk();
		bool IsRewitable();
		bool IsEmulated();
		bool IsSystem();
	};
}

#endif