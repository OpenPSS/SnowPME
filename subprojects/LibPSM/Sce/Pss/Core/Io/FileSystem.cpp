#include <Sce/Pss/Core/Io/FileSystem.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Io/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <LibShared.hpp>

#include <memory>
#include <vector>
#include <filesystem>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Io::Edata;

namespace Sce::Pss::Core::Io {

	FileSystem::FileSystem(const std::string& pathOnDisk, const std::string& sandboxPathName, bool rewritable, bool root, bool system) {
		this->pathInSandbox = sandboxPathName;
		this->pathOnDisk = pathOnDisk;
		this->rewritable = rewritable;
		this->system = system;
		this->root = root;

		std::filesystem::create_directories(std::filesystem::path(pathOnDisk));
	}

	std::string FileSystem::SandboxPath() {
		return this->pathInSandbox;
	}
	std::string FileSystem::PathOnDisk() {
		return this->pathOnDisk;
	}
	
	bool FileSystem::IsSystem() {
		return this->system;
	}
	
	bool FileSystem::IsWritable() {
		return this->rewritable && !this->IsRoot();
	}

	bool FileSystem::IsRoot() {
		return this->root;
	}
}
