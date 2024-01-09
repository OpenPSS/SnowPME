#ifndef LIB_PSS_FILESYSTEM_H
#define LIB_PSS_FILESYSTEM_H 1

#include <string>
#include <filesystem>

namespace Sce::Pss::Core::Io {
	class FileSystem {
	private:
		bool rw = false;
		bool emulated = false;
		std::string pathOnDisk = "";
		std::string sandboxPath = "";
	public:
		FileSystem(std::string filesystemPath, std::string sandboxPathName, bool rewritable, bool emulated);
		~FileSystem();

		std::string SandboxPath();
		std::string PathOnDisk();
		bool IsEncrypted();
		bool IsRewitable();
		bool IsEmulated();
	};
}

#endif