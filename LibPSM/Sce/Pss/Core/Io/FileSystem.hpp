#ifndef LIB_PSM_FILESYSTEM_H
#define LIB_PSM_FILESYSTEM_H 1

#include <string>
#include <filesystem>

namespace Sce::Pss::Core::Io {
	class FileSystem {
	private:
		std::byte gamekey[0x20];
		bool hasEdata;
		bool rw;
		bool emulated;
		std::string pathOnDisk;
		std::string sandboxPath;
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