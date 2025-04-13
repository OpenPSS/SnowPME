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


namespace Sce::Pss::Core::Io {
	using namespace Sce::Pss::Core::System;
	using namespace Shared::String;
	using namespace Shared;

	DirectoryIterator::DirectoryIterator(std::string relativePath, bool recursive) {
		this->startFolderSandboxPath = Sandbox::GetUniqueObject()->AbsolutePath(relativePath);

		StackItem item = StackItem();
		item.positionInFolder = 0;
		item.sandboxPath = this->startFolderSandboxPath;
		item.realPath = Sandbox::GetUniqueObject()->LocateRealPath(item.sandboxPath, false);
		item.relativePath = "";
		item.iterator = new std::filesystem::directory_iterator(item.realPath);

		this->iterPos = 0;
		this->folderStack.push_back(item);
		this->recursive = recursive;
	}

	DirectoryIterator::~DirectoryIterator() {
		for (StackItem item : this->folderStack) {
			delete item.iterator;
		}
		this->folderStack.clear();
	}

	size_t DirectoryIterator::Tell() {
		return this->iterPos;
	}

	int DirectoryIterator::Next(ScePssFileInformation_t* pathInfo) {

		int depth = this->folderStack.size() - 1;
		StackItem item = this->folderStack.at(depth);

		std::filesystem::directory_iterator iterator = *item.iterator;
		
		ScePssFileInformation_t psmPathInformation;

		if ( (Config::TargetImplementation == RuntimeImplementation::Windows) && this->iterPos == 0) {
			psmPathInformation = Sandbox::GetUniqueObject()->Stat(item.sandboxPath, Path::Combine(item.relativePath, "."));
		}
		else if((Config::TargetImplementation == RuntimeImplementation::Windows) && this->iterPos == 1) {

			StackItem prevStackItem = item;
			if (depth > 0)
				prevStackItem = this->folderStack.at(depth - 1);

			psmPathInformation = Sandbox::GetUniqueObject()->Stat(prevStackItem.sandboxPath, Path::Combine(item.relativePath, ".."));
		}
		else {
			if (iterator == std::filesystem::end(iterator)) {
				delete item.iterator; // delete current iterator
				this->folderStack.pop_back();// Pop from the stack, and set current directory to the previous one.

				if (depth > 0) {
					return this->Next(pathInfo);
				}
				else {
					return PSM_ERROR_PATH_NOT_FOUND;
				}
			}

			std::string nextPath = iterator->path().string();

			std::string filename = Path::GetFilename(nextPath);
			std::string sandboxAbsPath = Path::Combine(item.sandboxPath, filename);
			std::string sandboxRelativePath = Path::Combine(item.relativePath, filename);

			psmPathInformation = Sandbox::GetUniqueObject()->Stat(sandboxAbsPath, sandboxRelativePath);

			iterator++;

			if (Sandbox::GetUniqueObject()->IsDirectory(sandboxAbsPath) && this->recursive) {
				// Push to the stack, and set current directory to the new one.

				StackItem nitem = StackItem();
				nitem.sandboxPath = sandboxAbsPath;
				nitem.relativePath = sandboxRelativePath;
				nitem.realPath = Sandbox::GetUniqueObject()->LocateRealPath(sandboxAbsPath, false);

				nitem.iterator = new std::filesystem::directory_iterator(nitem.realPath);
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
