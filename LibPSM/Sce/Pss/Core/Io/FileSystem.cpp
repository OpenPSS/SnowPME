#include <Sce/Pss/Core/Io/FileSystem.hpp>

#include <vector>
#include <filesystem>

namespace Sce::Pss::Core::Io {
	 
	FileSystem::FileSystem(std::string pathOnDisk, std::string sandboxPathName, bool rewritable, bool emulated, bool system) {
		this->sandboxPath = sandboxPathName;
		this->pathOnDisk = pathOnDisk;
		this->rw = rewritable;
		this->system = system;
		this->emulated = emulated;

		std::filesystem::create_directories(std::filesystem::path(pathOnDisk));
	}
	FileSystem::~FileSystem() {

	}

	std::string FileSystem::SandboxPath() {
		return this->sandboxPath;
	}
	std::string FileSystem::PathOnDisk() {
		return this->pathOnDisk;
	}
	bool FileSystem::IsSystem() {
		return this->system;
	}
	bool FileSystem::IsRewitable() {
		
		if (!this->rw || this->IsEmulated())
			return false;
		else
			return true;
	}

	bool FileSystem::IsEmulated() {
		return this->emulated;
	}
}
