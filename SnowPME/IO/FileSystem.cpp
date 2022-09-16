#include <IO/FileSystem.hpp>
#include <IO/Path.hpp>
#include <Util/StringUtils.hpp>

#include <vector>
using namespace SnowPME::Util;

namespace SnowPME::IO {
	 
	FileSystem::FileSystem(std::string filesystemPath, std::string sandboxPathName, bool rewritable) {
		sandboxPath = sandboxPathName;
		pathOnDisk = filesystemPath;
		rw = rewritable;

		// TODO: Implement encryption
		hasEdata = false;
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

}
