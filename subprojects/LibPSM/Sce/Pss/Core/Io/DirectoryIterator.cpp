#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Io/DirectoryIterator.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Debug/Logger.hpp>

#include <vector>
#include <string>
#include <filesystem>
#include <cstring>

#include <LibShared.hpp>

using namespace Sce::Pss::Core::System;
using namespace Shared::String;
using namespace Shared;

namespace Sce::Pss::Core::Io {


	DirectoryIterator::DirectoryIterator(std::string relativePath, bool recursive) {
		LOCK_GUARD();
		StackItem item;
		item.positionInFolder = 0;
		item.pathInSandbox = this->startFolderSandboxPath;
		item.pathOnDisk = Sandbox::GetUniqueObject()->LocateRealPath(item.pathInSandbox, false);
		item.relativePath = "";
		item.iterator = new std::filesystem::directory_iterator(item.pathOnDisk);

		this->iterPos = 0;
		this->folderStack.push_back(item);
		this->recursive = recursive;
	}

	DirectoryIterator::~DirectoryIterator() {
		this->Close();
	}


	void DirectoryIterator::Close() {
		LOCK_GUARD();
		if (!this->opened) return;

		for (StackItem item : this->folderStack) {
			delete item.iterator;
		}
		this->folderStack.clear();

		this->opened = false;
	}

	bool DirectoryIterator::IsDirectory() {
		return true;
	}
	
	bool DirectoryIterator::IsEncrypted() {
		return false;
	}

	bool DirectoryIterator::IsOpen() {
		LOCK_GUARD();
		return this->opened;
	}

	uint64_t DirectoryIterator::Tell() {
		LOCK_GUARD();
		if (!this->opened) return 0;
		return this->iterPos;
	}

	uint32_t DirectoryIterator::Read(void* buffer, uint32_t length) {
		LOCK_GUARD();
		if (length == 0) return 0;
		if (length % sizeof(ScePssFileInformation_t) != 0) return 0;

		ScePssFileInformation_t* fileInfoArray = static_cast<ScePssFileInformation_t*>(buffer);

		uint32_t total = length / sizeof(ScePssFileInformation_t);
		uint32_t got = 0;

		for (got = 0; got < total; got++) if (this->Next(&fileInfoArray[got]) != PSM_ERROR_NO_ERROR) break;

		return got * sizeof(ScePssFileInformation_t);
	}

	int DirectoryIterator::Next(ScePssFileInformation_t* pathInfo) {		
		// dont allow if the file is already closed
		if (!this->opened) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		int depth = this->folderStack.size() - 1;
		StackItem item = this->folderStack.at(depth);

		std::filesystem::directory_iterator iterator = *item.iterator;
		
		ScePssFileInformation_t psmPathInformation;

		if ((Config::TargetImplementation == RuntimeImplementation::Windows) && this->iterPos == 0) {
			psmPathInformation = Sandbox::GetUniqueObject()->Stat(item.pathInSandbox, Path::Combine(item.relativePath, "."));
		}
		else if((Config::TargetImplementation == RuntimeImplementation::Windows) && this->iterPos == 1) {

			StackItem prevStackItem = item;
			if (depth > 0)
				prevStackItem = this->folderStack.at(depth - 1);

			psmPathInformation = Sandbox::GetUniqueObject()->Stat(prevStackItem.pathInSandbox, Path::Combine(item.relativePath, ".."));
		}
		else {
			if (iterator == std::filesystem::end(iterator)) {
				delete item.iterator; // delete current iterator
				this->folderStack.pop_back(); // Pop from the stack, and set current directory to the previous one.

				if (depth > 0) {
					return this->Next(pathInfo);
				}
				else {
					return PSM_ERROR_PATH_NOT_FOUND;
				}
			}

			std::string nextPath = iterator->path().string();

			std::string filename = Path::GetFilename(nextPath);
			std::string sandboxAbsPath = Path::Combine(item.pathInSandbox, filename);
			std::string sandboxRelativePath = Path::Combine(item.relativePath, filename);

			psmPathInformation = Sandbox::GetUniqueObject()->Stat(sandboxAbsPath, sandboxRelativePath);

			iterator++;

			if (Sandbox::GetUniqueObject()->IsDirectory(sandboxAbsPath) && this->recursive) {
				// Push to the stack, and set current directory to the new one.

				StackItem nitem;
				nitem.pathInSandbox = sandboxAbsPath;
				nitem.relativePath = sandboxRelativePath;
				nitem.pathOnDisk = Sandbox::GetUniqueObject()->LocateRealPath(sandboxAbsPath, false);

				nitem.iterator = new std::filesystem::directory_iterator(nitem.pathOnDisk);
				nitem.positionInFolder = 0;

				this->folderStack.push_back(nitem);
			}
		}

		std::memcpy(pathInfo, &psmPathInformation, sizeof(ScePssFileInformation_t));
		item.positionInFolder++;
		this->iterPos++;
		return PSM_ERROR_NO_ERROR;
	}

}
