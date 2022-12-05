#include <Sce/Pss/Core/Io/FileSystem.hpp>
#include <Sce/Pss/Core/Io/Path.hpp>

#include <vector>
#include <filesystem>

#include <LibSnowPME.hpp>
using namespace SnowPME::Util;

namespace Sce::Pss::Core::Io {
	 
	FileSystem::FileSystem(std::string pathOnDisk, std::string sandboxPathName, bool rewritable, bool emulated) {
		this->sandboxPath = sandboxPathName;
		this->pathOnDisk = pathOnDisk;
		this->rw = rewritable;

		std::filesystem::create_directories(std::filesystem::path(pathOnDisk));

		this->emulated = emulated;

		// TODO: Implement encryption
		this->hasEdata = false;
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
		
		if (this->IsEncrypted() || !this->rw || this->IsEmulated())
			return false;
		else
			return true;
	}

	bool FileSystem::IsEmulated() {
		return this->emulated;
	}
}
