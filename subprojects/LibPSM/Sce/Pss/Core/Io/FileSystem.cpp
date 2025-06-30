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

	int FileSystem::readEdataList(PsmDrm* psmDrm) {
		int res = PSM_ERROR_NO_ERROR;

		if (this->IsWritable() || this->IsSystem())
			return PSM_ERROR_COMMON_IO;

		Logger::Debug("reading psse list.");

		std::filesystem::path psseListFile = std::filesystem::path(this->PathOnDisk()).append("psse.list");
		std::filesystem::path edataListFile = std::filesystem::path(this->PathOnDisk()).append("edata.list");

		if (std::filesystem::exists(psseListFile) || std::filesystem::exists(edataListFile)) { // check either psse.list or edata.list exist
			// read psse.list
			std::unique_ptr<EdataStream> str = nullptr;

			// if no psmDrm object cannot decrypt psse.list file, and must use edata.list.
			if(psmDrm != nullptr)
				str = std::make_unique<EdataStream>(psseListFile.string(), std::ios::binary | std::ios::in, psmDrm, nullptr);

			if (str == nullptr || str->GetError() == PSM_ERROR_NOT_FOUND) { // if that not exist, open edata.list
				Logger::Debug("fallback on reading edata.list.");
				str = std::make_unique<EdataStream>(edataListFile.string(), std::ios::binary | std::ios::in, psmDrm, nullptr);
				RETURN_ERRORABLE_SMARTPTR(str);
			}

			// allocate memory for the full psse.list file
			std::shared_ptr<HeapAllocator> heapAlloc = HeapAllocator::UniqueObject();
			char* psseLstData = reinterpret_cast<char*>(heapAlloc->sce_psm_malloc(static_cast<int>(str->Length())));

			// read the psse.list into the memory just allocated.
			int totalRead = str->Read(psseLstData, static_cast<uint32_t>(str->Length()));

			if (totalRead == str->Length()) { // if the total bytes read is the same as the filesize
				std::string edataList = std::string(psseLstData, static_cast<size_t>(str->Length())); // create a std::string from the psse.list data
				this->edataList = new EdataList(edataList); // create a psse.list object.
			}
			else {
				res = PSM_ERROR_COMMON_IO;
			}

			heapAlloc->sce_psm_free(psseLstData);
		}
		return res;
	}

	FileSystem::~FileSystem() {
		if (this->edataList != nullptr)
			delete this->edataList;
	}
	EdataList* FileSystem::GetEdataList(PsmDrm* psmDrm) {
		if (this->edataList == nullptr) {
			int err = this->readEdataList(psmDrm);
			if (err == PSM_ERROR_NO_ERROR) {
				return this->edataList;
			}
		}

		return this->edataList;
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
