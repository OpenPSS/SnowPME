#include <Sce/Pss/Core/Io/FileSystem.hpp>
#include <Sce/Pss/Core/Edata/EdataStream.hpp>
#include <Sce/Pss/Core/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Edata/PsmDrm.hpp>
#include <LibShared.hpp>

#include <vector>
#include <filesystem>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Edata;

namespace Sce::Pss::Core::Io {
	 
	FileSystem::FileSystem(std::string pathOnDisk, std::string sandboxPathName, bool rewritable, bool emulated, bool system) {
		this->sandboxPath = sandboxPathName;
		this->pathOnDisk = pathOnDisk;
		this->rw = rewritable;
		this->system = system;
		this->emulated = emulated;

		std::filesystem::create_directories(std::filesystem::path(pathOnDisk));
	}

	int FileSystem::readEdataList(PsmDrm* psmDrm) {
		int res = PSM_ERROR_NO_ERROR;

		if (this->IsRewitable() || this->IsSystem())
			return PSM_ERROR_COMMON_IO;

		Logger::Debug("reading psse list.");

		std::filesystem::path psseListFile = std::filesystem::path(this->PathOnDisk()).append("psse.list");
		std::filesystem::path edataListFile = std::filesystem::path(this->PathOnDisk()).append("edata.list");

		if (std::filesystem::exists(psseListFile) || std::filesystem::exists(edataListFile)) { // check either psse.list or edata.list exist
			// read psse.list
			EdataStream* str = nullptr;

			// if no psmDrm object cannot decrypt psse.list file, and must use edata.list.
			if(psmDrm != nullptr)
				EdataStream* str = new EdataStream(psseListFile.string(), std::ios::binary | std::ios::in, psmDrm, nullptr);

			if (str->GetError() == PSM_ERROR_NOT_FOUND) { // if that not exist, open edata.list
				if(str != nullptr)
					delete str;

				Logger::Debug("reading edata.list.");
				str = new EdataStream(edataListFile.string(), std::ios::binary | std::ios::in, psmDrm, nullptr);
				ReturnErrorable(str);
			}
			// allocate memory for the full psse.list file 
			char* psseLstData = new char[str->Filesize()];

			// read the psse.list into the memory just allocated.
			int totalRead = str->Read(psseLstData, str->Filesize());

			if (totalRead == str->Filesize()) { // if the total bytes read is the same as the filesize
				std::string edataList = std::string(psseLstData, str->Filesize()); // create a std::string from the psse.list data
				this->edataList = new EdataList(edataList); // create a psse.list object.
			}
			else {
				res = PSM_ERROR_COMMON_IO;
			}

			delete[] psseLstData;
			delete str;
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
