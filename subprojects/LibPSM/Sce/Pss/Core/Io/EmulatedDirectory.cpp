#include <Sce/Pss/Core/Io/EmulatedDirectory.hpp>
#include <LibShared.hpp>
#include <cstring>

using namespace Shared;
using namespace Shared::String;

namespace Sce::Pss::Core::Io {

	uint64_t EmulatedDirectory::Tell() {
		LOCK_GUARD();
		return this->position;
	}
	void EmulatedDirectory::Close() {
		LOCK_GUARD();
		this->opened = false;
	}

	uint32_t EmulatedDirectory::Read(void* buffer, uint32_t length) {
		if (length == 0) return 0;
		if (length % sizeof(ScePssFileInformation_t) != 0) return 0;

		ScePssFileInformation_t* fileInfoArray = static_cast<ScePssFileInformation_t*>(buffer);

		uint32_t total = length / sizeof(ScePssFileInformation_t);
		uint32_t got = 0;

		for (got = 0; got < total; got++) if (this->Next(&fileInfoArray[got]) != PSM_ERROR_NO_ERROR) break;

		return got * sizeof(ScePssFileInformation_t);
	}
	
	int EmulatedDirectory::Next(ScePssFileInformation_t* pathInfo) {
		LOCK_GUARD();
		if (!this->opened) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		uint64_t effectivePosition = this->position;
		this->position++;

		pathInfo->tCreationTime = std::time(0);
		pathInfo->tLastAccessTime = std::time(0);
		pathInfo->tLastWriteTime = std::time(0);

		/* 
		* not sure if ../ ./ is present on root paths; even on windows; need to check 
		*/
		
		if (effectivePosition < this->subdirectories.size()) {
			EmulatedDirectoryEntry entry = this->subdirectories.at(effectivePosition);

			if (!entry.file)	pathInfo->uFlags |= SCE_PSS_FILE_FLAG_DIRECTORY;
			if (entry.readonly) pathInfo->uFlags |= SCE_PSS_FILE_FLAG_READONLY;
			pathInfo->uFileSize = entry.size;

			strncpy(pathInfo->szName, Path::Combine(this->directoryName, entry.name).c_str(), PSM_PATH_MAX);
		}
		else {
			return PSM_ERROR_PATH_NOT_FOUND;
		}

		return PSM_ERROR_NO_ERROR;

	}

	bool EmulatedDirectory::IsDirectory() {
		return true;
	}

	bool EmulatedDirectory::IsEncrypted() {
		return false;
	}

	bool EmulatedDirectory::IsRewritable() {
		return false;
	}

	bool EmulatedDirectory::IsOpen() {
		LOCK_GUARD();
		return this->opened;
	}

	EmulatedDirectory::EmulatedDirectory(std::string rootDirectoryName, std::vector<EmulatedDirectoryEntry>& subDirectories) {
		this->subdirectories = subDirectories;
		this->directoryName = rootDirectoryName;
	}
	EmulatedDirectory::~EmulatedDirectory() {
		subdirectories.clear();
	}
}