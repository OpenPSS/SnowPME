#include <IO/FileSystem.hpp>
#include <IO/Path.hpp>
#include <Util/StringUtils.hpp>

#include <vector>
#include <filesystem>
using namespace SnowPME::Util;

namespace SnowPME::IO {
	 
	FileSystem::FileSystem(std::string pathOnDisk, std::string sandboxPathName, bool rewritable) {
		this->sandboxPath = sandboxPathName;
		this->pathOnDisk = pathOnDisk;
		this->rw = rewritable;

		std::filesystem::create_directories(std::filesystem::path(pathOnDisk));
		
		// TODO: Implement encryption and emulated dirs
		this->hasEdata = false;
		this->emulated = false;
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
		return this->hasEdata;
	}
	bool FileSystem::IsRewitable() {
		
		if (this->IsEncrypted() || !this->rw)
			return false;
		else
			return true;
	}

	bool FileSystem::IsEmulated() {
		return this->emulated;
	}
}
