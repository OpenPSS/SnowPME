#include <Sce/Pss/Core/Io/Edata/EdataList.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <string>

using namespace Shared::String;
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Memory;

namespace Sce::Pss::Core::Io::Edata {
	std::vector<std::string> EdataList::edataFilesList;

	bool EdataList::IsFileInEdata(const std::string& path) {
		if (edataFilesList.empty()) return false;

		for (const std::string& edataFile : edataFilesList) {
			if (Format::ToLower(Path::ChangeSlashesToPsmStyle(path)).ends_with(Format::ToLower(Path::ChangeSlashesToPsmStyle(edataFile)))) {
				Logger::Debug("[EdataList] Found " + path + " in edata list");
				return true;
			}
		}
		Logger::Debug("[EdataList] Could not find " + path + " in edata list");
		return false;
	}


	int EdataList::ReadPsseOrEdataList(uint8_t klicensee[0x10], Sandbox* sandbox) {
		Logger::Debug("[EdataList] Reading "+ PsseListPath);

		if (sandbox == nullptr && Sandbox::UniqueObjectExists()) sandbox = Sandbox::UniqueObject().get();
		if (sandbox == nullptr) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		std::string psseListFile = sandbox->LocateRealPath(PsseListPath);
		std::string edataListFile = sandbox->LocateRealPath(EdataListPath);

		if (std::filesystem::exists(psseListFile) || std::filesystem::exists(edataListFile)) { // check either psse.list or edata.list exist
			// read psse.list
			std::unique_ptr<EdataStream> str = nullptr;

			// if no psmDrm object cannot decrypt psse.list file, and must use edata.list.
			if (klicensee != nullptr) str = std::make_unique<EdataStream>(psseListFile, std::ios::binary | std::ios::in, klicensee, true);

			if (str == nullptr || str->GetError() == PSM_ERROR_NOT_FOUND) { // if that not exist, open edata.list
				Logger::Debug("[EdataList] falling back on reading: " + EdataListPath);
				str = std::make_unique<EdataStream>(edataListFile, std::ios::binary | std::ios::in, klicensee, true);
				RETURN_ERRORABLE_SMARTPTR(str);
			}

			// allocate memory for the full psse.list file
			std::vector<char> fileData(str->Length());

			// read the psse.list into the memory just allocated.
			uint32_t totalRead = str->Read(fileData.data(), static_cast<uint32_t>(str->Length()));
			if (totalRead == str->Length()) { // if the total bytes read is the same as the filesize
				std::string edataList = std::string(fileData.data(), static_cast<size_t>(str->Length())); // create a std::string from the psse.list data
				parseEdataList(edataList, sandbox); // create a psse.list object.
			}
			else {
				return PSM_ERROR_COMMON_IO;
			}
		}
		return PSM_ERROR_NO_ERROR;
	}


	void EdataList::parseEdataList(const std::string& psseListData, Sandbox* sandbox) {
		std::vector<std::string> psseFilesList = Format::Split(Format::Replace(psseListData, "\r", ""), "\n");

		for (const std::string& psseFile : psseFilesList) {
			if (psseFile.empty()) continue;

			std::string sandboxPath = Path::Combine("/Application", psseFile);
			std::string realPath = sandbox->LocateRealPath(sandboxPath);

			Logger::Debug("[EdataList] Registering file: " + sandboxPath);
			edataFilesList.push_back(realPath);
		}
	}
}