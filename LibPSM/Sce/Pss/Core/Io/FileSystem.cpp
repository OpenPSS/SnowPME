#include <Sce/Pss/Core/Io/FileSystem.hpp>

#include <vector>
#include <filesystem>

namespace Sce::Pss::Core::Io {
	 
	FileSystem::FileSystem(std::string pathOnDisk, std::string sandboxPathName, bool rewritable, bool emulated) {
		this->sandboxPath = sandboxPathName;
		this->pathOnDisk = pathOnDisk;
		this->rw = rewritable;

		std::filesystem::create_directories(std::filesystem::path(pathOnDisk));

		this->emulated = emulated;
	}
	FileSystem::~FileSystem() {

	}

	std::string FileSystem::SandboxPath() {
		return this->sandboxPath;
	}
	std::string FileSystem::PathOnDisk() {
		return this->pathOnDisk;
	}
	bool FileSystem::IsEncrypted() {
		return false;
	}
	bool FileSystem::IsRewitable() {
		
		if (this->IsEncrypted() || !this->rw || this->IsEmulated())
			return false;
		else
			return true;
	}

	bool FileSystem::IsEmulated() {
		return this->emulated;
	}
}
