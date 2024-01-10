#ifndef LIB_PSS_DIRECTORY_ITERATOR_H
#define LIB_PSS_DIRECTORY_ITERATOR_H 1
#include <vector>
#include <string>
#include <filesystem>
#include <mono/mono.h>
#include <Sce/Pss/Core/Io/StackItem.hpp>

namespace Sce::Pss::Core::Io {

	class DirectoryIterator {
	private:
		std::vector<StackItem> folderStack = std::vector<StackItem>();
		std::string startFolderSandboxPath = "";
		size_t iterPos = 0;
		bool recursive = false;
	public:
		DirectoryIterator(std::string sandboxedFolder, bool recursive);
		~DirectoryIterator();
		int Next(ScePssFileInformation_t* pathInfo);
		size_t Tell();
	};
}
#endif